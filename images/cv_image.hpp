// coding: utf-8
// !\file image/cv_image.hpp
// !\brief Класс, предоставляющий "обертку" для различных представлений изображений из библиотеки OpenCV.
// !\autor Рябцев В.В.

#if !defined(_FLARE_PROCESSING_IMAGE_CV_IMAGE_HPP)
#define _FLARE_PROCESSING_IMAGE_CV_IMAGE_HPP

#include <opencv2/opencv.hpp>

//! Класс, предоставляющий "обертку" для различных представлений изображений из библиотеки OpenCV.
class CVImage {
public:

  //! Именованное перечисление поддерживаемых форматов изображения.
  enum class Format {
    RGB,
    HSV
  };

  //! Конструктор.
  //! \param fileName - имя файла, содержащего изображение.
  //CVImage(cv::String& fileName = "");

  //! Возвращает представление изображения в формате RGB.
  const cv::Mat& rgbImage() const;

  //! Возвращает представение изображения в формате HSV.
  const cv::Mat& hsvImage() const;

  //! Возвращает представление изображения в

private:
  cv::Mat rgbImage_;
  cv::Mat hsvImage_;
  cv::Mat grayscaleImage_;
};

#endif // _FLARE_PROCESSING_IMAGE_CV_IMAGE_HPP
