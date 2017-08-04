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

  //! Выделяет границы текстовых блоков изображения.
  //! \param cvImage - обрабатываемое изображение.
  //! \param bwThresholdLevel - значение цветового порога для преобразования изображения из градаций серого в черно-белое.
  static std::vector<cv::Rect> detectTextBounds( const cv::Mat& cvImage, const double& bwThresholdLevel = 100. );


  //! Выделяет границы документа (страницы документа).
  //! \param cvImage - обрабатываемое изображение.
  //! \param bwThresholdLevel - значение цветового порога для преобразования изображения из градаций серого в черно-белое.
  static cv::Rect detectDocumentBounds( const cv::Mat& cvImage, const double& bwThresholdLevel = 25. );

  //! Создает изображение с отрисованными границами документа.
  static cv::Mat createDocumentBoundedImage( const cv::Mat& cvImage, const cv::Rect& documentBounds = cv::Rect() );

  //! Создает изображение с отрисованными границами текстовых блоков.
  static cv::Mat createTextBoundedImage( const cv::Mat& image, const std::vector<cv::Rect>& textBounds = std::vector<cv::Rect>(0) );

  //! Возвращает уровень порога цвета для преобразования изображения из градаций серого в черно-белое.
  const double& bwThresholdLevel() const;

  //! Устанавливает уровень порога цвета для преобразования изображения из градаций серого в черно-белое.
  void setBwThresholdLevel(const double &level);

private:

  double bwThresholdLevel_;         //!< Значение уровня порога цвета для преобразования изображения из градаций серого в черно-белое.

private:

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


inline
const double &ImageProcessor::bwThresholdLevel() const
{
  return bwThresholdLevel_;
}

inline
void ImageProcessor::setBwThresholdLevel(const double& level)
{
  bwThresholdLevel_ = level;
}

#endif // _DOCUMENT_RECOGNIZER_IMAGES_IMAGE_PROCESSOR_HPP

