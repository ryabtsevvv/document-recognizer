// coding: utf-8
// !\file gui/cv_image_widget.hpp
// !\brief Виджет для отображения графических файлов в формате OpenCV.
// !\author Рябцев В.В.

#if !defined(_GUI_CV_IMAGE_WIDGET_HPP)
#define _GUI_CV_IMAGE_WIDGET_HPP

#include <QImage>
#include <QWidget>

#include <opencv2/opencv.hpp>

class QLabel;
class QScrollArea;

//! Класс, реализующий виджет, служащий для отображения графических файлов.
class ImageWidget: public QWidget {

  Q_OBJECT

public:

  explicit ImageWidget(QWidget * parent = nullptr);

public slots:

  void showImage(const cv::Mat& cvImage);

private:
  static double defaultScaleFactor();
  void setImage(const QImage& image);

  QLabel * imageLabel_;
  QScrollArea * scrollArea_;
  double scaleFactor_;

}; // class CVImageWidget

inline
double ImageWidget::defaultScaleFactor() {
  return 1.;
}

#endif // _GUI_CV_IMAGE_WIDGET_HPP
