// coding: utf-8
//! \file images/page_image.hpp
//! \brief Класс, соответствующий изображению страницы документа.
//! \author Рябцев В.В.

#if !defined(_DOCUMENT_RECOGNIZER_DOCUMENTS_PAGE_IMAGE_HPP)
#define _DOCUMENT_RECOGNIZER_DOCUMENTS_PAGE_IMAGE_HPP

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

#include <images/recognizable_object.hpp>

class ImageProcessor;

//! Класс, соответствующий изображению страницы документа.
class PageImage: public RecognizableObject {

  friend class ImageProcessor;

public:

  //!  Конструктор.
  PageImage() = default;

  //! Конструктор.
  //! Создает объект по существующему графическому представлению.
  PageImage(const cv::Mat& image);

  //! Возвращает графическое представление страницы документа.
  const cv::Mat& image() const;

  //! Возвращает графическое представление страницы документа, содержащее выделенный текст.
  const cv::Mat& borderedTextImage() const;

  //! Устанавливает новое графическое представление страницы документа.
  void setImage(const cv::Mat& image);

  //! Возвращает набор прямоугольних контуров, являющихся границами текста,
  //! присутствующего на данной странице.
  const std::vector< cv::Rect >& textBounds() const;

  //! Возвращает кольчество обнаруженных текстовых блоков.
  const size_t textBlocksNumber() const;

private:

  cv::Mat image_;                             //!< Графическое представление данной страницы.
  std::vector< cv::Rect > textBounds_;        //!< Прямоугольники, являющиеся границами текста на данной странице.
  cv::Mat boundedTextImage_;                 //!< Графическое представение данной страницы содержащее выделенный в рамках текст.

}; // class PageImage

inline
const size_t PageImage::textBlocksNumber() const
{
  return textBounds_.size();
}

#endif // _DOCUMENT_RECOGNIZER_DOCUMENTS_PAGE_IMAGE_HPP
