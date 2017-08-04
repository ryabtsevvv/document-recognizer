#include "page_image.hpp"
#include <images/image_processor.hpp>

PageImage::PageImage(const cv::Mat &image):
  image_( image ),
  textBounds_( ImageProcessor::detectTextBounds(image_) ),
  boundedTextImage_( ImageProcessor::createTextBoundedImage( image_, textBounds_) )
{}

const cv::Mat &PageImage::image() const
{
  return image_;
}

const cv::Mat &PageImage::borderedTextImage() const
{
  return boundedTextImage_;
}

void PageImage::setImage(const cv::Mat &image)
{
  image_ = image;
  textBounds_ = ImageProcessor::detectTextBounds(image_);
  boundedTextImage_ = ImageProcessor::createTextBoundedImage(image_, textBounds_);
}
