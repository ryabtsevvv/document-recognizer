// coding: utf-8
//! \file image/image_processor.hpp
//! \brief Класс, выполняющий обработку изображений.
//! \author Рябцев В.В.
//! \todo Разбить данный класс на несколько классов, выполняющих задачи определенного рода.

#if !defined(_DOCUMENT_RECOGNIZER_IMAGE_IMAGES_PROCESSOR_HPP)
#define _DOCUMENT_RECOGNIZER_IMAGE_IMAGES_PROCESSOR_HPP

#include <QImage>
#include <vector>
#include <opencv2/core/types.hpp>


namespace ImageProcessorConstants {
  const double minimialVerticalTextSizeToPageSize = 1. / 180.;    //!< Соотношение верно для паспорта РФ.
  const double minimialHorizontalTextSizeToPageSize = 4. / 125.;    //!< Соотношение верно для паспорта РФ.
}

//! Класс, выполняющий обработку изображений,
//! в том числе, преобразование между пространствами цветов,
//! выделение определенных областей изображения,
//! поиск текста и т.д.
class ImageProcessor {
public:

  //! Преобразует изображение из нативного формата OpenCV
  //! в нативный формат Qt.
  static QImage toQImage( const cv::Mat& cvImage );

  static std::vector<cv::Rect> detectTextBounds( const cv::Mat& cvImage );

  static cv::Mat createTextBoundedImage( const cv::Mat& image, const std::vector<cv::Rect>& textBounds = std::vector<cv::Rect>(0) );

private:

  //double thresholdLevel_;

  static const size_t BYTES_IN_RGB888_PIXEL = 3;

  //! Возвращает признак того, является ли  прямоугольный контур горизонтальным.
  static bool isHorizontal(const cv::Rect& rect);

  //! Возвращает признак того, является ли  прямоугольный контур вертикальным.
  static bool isVertical(const cv::Rect& rect);

  //! Возвращает признак приемлемого для модели прямоугольного горизонтального контура.
  static bool isHorizontalAccepted(const cv::Rect& rect, const cv::Mat& image);

  //! Возвращает признак приемлемого для модели прямоугольного вертикального контура.
  static bool isVerticalAccepted(const cv::Rect& rect, const cv::Mat& image);

}; // class ImageProcessor

#endif // _DOCUMENT_RECOGNIZER_IMAGES_IMAGE_PROCESSOR_HPP

