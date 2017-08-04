// coding: utf-8

#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPalette>
#include <QScrollArea>

#include <opencv2/opencv.hpp>

#include <images/image_processor.hpp>
#include "cv_image_widget.hpp"

ImageWidget::ImageWidget(QWidget *parent):
  QWidget(parent),
  imageLabel_(new QLabel),
  scrollArea_(new QScrollArea),
  scaleFactor_(defaultScaleFactor())
{
  QLayout * widgetLayout = new QGridLayout(this);
  widgetLayout->addWidget(scrollArea_);

  scrollArea_->setVisible(false);
  scrollArea_->setBackgroundRole(QPalette::Dark);
  scrollArea_->setWidget(imageLabel_);

  imageLabel_->setBackgroundRole(QPalette::Base);
  imageLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel_->setScaledContents(true);
}

void ImageWidget::showImage(const cv::Mat &cvImage)
{
  QImage qImage = ImageProcessor::toQImage(cvImage);
  setImage(qImage);
}

void ImageWidget::setImage(const QImage &image)
{
  scrollArea_->setVisible(true);          //!< \todo Разобраться, почему для корректной работы программы эта строчка должна идти первой.
  scaleFactor_ = defaultScaleFactor();

  QPixmap map = QPixmap::fromImage(image);
  imageLabel_->setPixmap(map);
  imageLabel_->adjustSize();
}
