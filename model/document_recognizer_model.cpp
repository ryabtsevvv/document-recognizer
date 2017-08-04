#include <opencv2/opencv.hpp>
#include "document_recognizer_model.hpp"

bool DocumentRecognizerModel::loadImage(const QString &fileName)
{
  bool result(false);

  if( !fileName.isEmpty() ) {
    cv::Mat image = cv::imread( fileName.toStdString().c_str() );

    if( !image.empty() ) {
      currentPage_.setImage(image);
      emit imageLoaded(fileName);
      result = true;
    }
  }
  else {
    emit imageLoadingFailed(fileName);
    result = false;
  }

  return result;
}
