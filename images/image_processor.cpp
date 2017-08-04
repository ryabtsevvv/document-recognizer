// coding: utf-8

#include <stdexcept>
#include <string>
#include <opencv2/opencv.hpp>

#include "image_processor.hpp"

QImage ImageProcessor::toQImage(const cv::Mat &cvImage)
{
  cv::Mat temp;
  switch (cvImage.type()) {
  case CV_8UC1:
    cvtColor(cvImage, temp, CV_GRAY2RGB);
    break;
  case CV_8UC3:
    cvtColor(cvImage, temp, CV_BGR2RGB);
    break;
  default:
    throw std::runtime_error("Unsupported image type. Exception from file " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__));
  } // switch( ... )

  assert( temp.isContinuous() );

  QImage result(static_cast<const uchar*>(temp.data), temp.cols, temp.rows,  temp.step, QImage::Format_RGB888);
  result.bits();    // Осуществляет физическое копирование данных, без этой строчки все перестанет работать после удаления temp.
  return result;
}

//double ImageProcessor::defaultBwThresholdLevel = 100.;

std::vector<cv::Rect> ImageProcessor::detectTextBounds(const cv::Mat &cvImage, const double& bwThresholdLevel) {

  const double thresholdBinaryValue = 255.;

  int colsSize = 0.005 * cvImage.cols;
  if(colsSize < 9) { colsSize = 9; }
  int rowsSize = 0.005 * cvImage.rows;
  if(rowsSize < 3) { rowsSize = 3; }

  cv::Mat grayscaleImage;
  cvtColor( cvImage, grayscaleImage, CV_BGR2GRAY );
  blur( grayscaleImage, grayscaleImage, cv::Size(3, 3) );

  cv::Mat gradient;
  cv::Mat morphKernel = cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( colsSize, rowsSize ) );
  cv::morphologyEx( grayscaleImage, gradient, cv::MORPH_GRADIENT, morphKernel );
  //blur( gradient, gradient, cv::Size(3, 3) );
  IF_DEBUG( cv::imwrite("gradient.jpg", gradient) );

  cv::Mat blackWhite;
  cv::threshold( gradient, blackWhite, bwThresholdLevel, thresholdBinaryValue, cv::THRESH_BINARY);
  IF_DEBUG( cv::imwrite("blackwhite.jpg", blackWhite) );

  cv::Mat connectedHRegions;
  morphKernel = cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 11, 7 ) );
  cv::morphologyEx( blackWhite, connectedHRegions, cv::MORPH_CLOSE, morphKernel );
  IF_DEBUG( cv::imwrite("connected.jpg", connectedHRegions) );


  std::vector< std::vector< cv::Point > > contours;
  std::vector< cv::Vec4i > hierarchy;
  cv::findContours( connectedHRegions, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

  std::vector< cv::Rect > boundingRect;

  for(int i = 0; i >= 0; i = hierarchy[i][0]) {
    cv::Rect rect = cv::boundingRect( contours[i] );
    if( ( isHorizontal(rect) && isHorizontalAccepted(rect, connectedHRegions) ) ||
        ( isVertical(rect) && isVerticalAccepted(rect, connectedHRegions) )
    )
    {
      boundingRect.push_back(rect);
    }
  }

  return boundingRect;
}

cv::Rect ImageProcessor::detectDocumentBounds(const cv::Mat &cvImage, const double &bwThresholdLevel)
{
  const double thresholdBinaryValue = 255.;

  cv::Mat grayscaleImage;
  cvtColor( cvImage, grayscaleImage, CV_BGR2GRAY );
  //blur( grayscaleImage, grayscaleImage, cv::Size(7, 7) );

  cv::Mat gradient;
  cv::Mat morphKernel = cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 7, 7 ) );
  cv::morphologyEx( grayscaleImage, gradient, cv::MORPH_GRADIENT, morphKernel );
  blur( gradient, gradient, cv::Size(7, 7) );
  IF_DEBUG( cv::imwrite("gradient_doc.jpg", gradient) );

  cv::Mat blackWhite;
  cv::threshold( gradient, blackWhite, bwThresholdLevel, thresholdBinaryValue, cv::THRESH_BINARY);
  IF_DEBUG( cv::imwrite("blackwhite_doc.jpg", blackWhite) );

  std::vector< std::vector< cv::Point > > contours;
  std::vector< cv::Vec4i > hierarchy;
  cv::findContours( blackWhite, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

  cv::Rect boundingRect;

  double largestArea = 0.;
  size_t largestContourIndex = 0;


  for( size_t i = 0U; i < contours.size(); ++i ) {
    double a = cv::contourArea( contours[i], false );
    if(a > largestArea) {
      largestArea = a;
      largestContourIndex = i;
    }
  }

  return cv::boundingRect( contours[largestContourIndex] );
}

cv::Mat ImageProcessor::createDocumentBoundedImage(const cv::Mat &image, const cv::Rect &documentBounds)
{
  cv::Mat result = image.clone();
  cv::rectangle( result, documentBounds, cv::Scalar( 0, 0, 255 ), 3, 8, 0 );
  return result;
}

bool ImageProcessor::isHorizontal(const cv::Rect &rect)
{
  return rect.width >= rect.height;
}

bool ImageProcessor::isVertical(const cv::Rect &rect)
{
  return !isHorizontal(rect);
}

bool ImageProcessor::isHorizontalAccepted(const cv::Rect &rect, const cv::Mat &image)
{
  const double horizontalRatioAcceptionLevel = 1.25;
  double ratio = (rect.height > 0) ? static_cast<double>(rect.width)/rect.height : 0.;
  return ( ratio > horizontalRatioAcceptionLevel ) && ( rect.width > image.cols * 0.001 ) && (rect.height > image.rows * 0.001);
}

bool ImageProcessor::isVerticalAccepted(const cv::Rect &rect, const cv::Mat &image)
{
  const double verticalRatioAcceptionLevel = 1.75;
  double ratio = (rect.width > 0) ? static_cast<double>(rect.height)/rect.width : 0.;
  return ( ratio > verticalRatioAcceptionLevel ) && ( rect.height > image.rows * 0.001 ) && (rect.width > image.cols * 0.001);
}

cv::Mat ImageProcessor::createTextBoundedImage(const cv::Mat &image, const std::vector<cv::Rect>& textBounds) {
  cv::Mat result = image.clone();
  if( textBounds.size() > 0U ) {
    for( auto i = 0U; i < textBounds.size(); ++i ) {
      cv::rectangle( result, textBounds[i], cv::Scalar( 0, 255 ,0 ), 3, 8, 0 );
    }
  }
  return result;
}

