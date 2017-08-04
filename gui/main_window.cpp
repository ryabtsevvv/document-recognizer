#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

#include <model/document_recognizer_model.hpp>

#include "control_widget.hpp"
#include "image_widget.hpp"
#include "main_window.hpp"
#include "ui_main_window.h"

DocumentRecognizerMainWindow::DocumentRecognizerMainWindow(DocumentRecognizerModel &model, QWidget *parent):
  QMainWindow(parent),
  model_(model),
  ui_(new Ui::DocumentRecognizerMainWindow),
  controlWidget_(new ControlWidget(this)),
  imageWidget_(new ImageWidget(this)),
  lastUsedDirectory_(QDir::homePath())
{
  ui_->setupUi(this);
  setCentralWidget(imageWidget_);

  QDockWidget * dockWidget = new QDockWidget(tr("Панель управления"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(controlWidget_);
  controlWidget_->adjustSize();
  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

  connectSignalsAndSlots();
}

DocumentRecognizerMainWindow::~DocumentRecognizerMainWindow()
{
  delete ui_;
}

void DocumentRecognizerMainWindow::connectSignalsAndSlots()
{
  connect( ui_->actionOpen, SIGNAL( triggered(bool) ), this, SLOT( openFile() ) );
  connect( &model_, SIGNAL( imageLoaded(const QString&) ),        this, SLOT( updateImage(const QString&) ) );
  connect( &model_, SIGNAL( imageLoadingFailed(const QString&) ), this, SLOT( showImageLoadingFailedDialog(const QString&) ) );
  connect( controlWidget_, SIGNAL( showTextBordersCheckBoxChecked(bool) ), this, SLOT( showTextBorders(bool) ) );
}


void DocumentRecognizerMainWindow::openFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open image file"), lastUsedDirectory_, tr("Images (*.jpg *.jpeg *.png)"));

  if(!fileName.isEmpty()) {
    lastUsedDirectory_ = QFileInfo(fileName).path();
  }

  model_.loadImage(fileName);
}

void DocumentRecognizerMainWindow::updateImage()
{
  const cv::Mat& imageToShow = controlWidget_->isShowTextBorderCheckBoxChecked() ?
                               model_.currentPage().borderedTextImage() : model_.currentPage().image();
  imageWidget_->showImage( imageToShow );
}

void DocumentRecognizerMainWindow::updateImage(const QString& fileName)
{
  updateImage();
  const cv::Mat& image = model_.currentPage().image();
  this->statusBar()->showMessage( tr("Файл: %1. Размер: %2 х %3").arg(fileName).arg(image.cols).arg(image.rows) );
}

void DocumentRecognizerMainWindow::showImageLoadingFailedDialog(const QString& fileName)
{
  QMessageBox::warning(this, tr("Ошибка загрузки изображения"),
                       tr("Ошибка при загрузке изображения.\n"
                          "Отображение файла %1 невозможно.").arg(fileName)
                       );
}

//! \todo Убрать временные заглушки в виде реализации через статические переменные.
void DocumentRecognizerMainWindow::showTextBorders(bool needShowTextBorders)
{
  static bool isBordersShowed = false;
  static bool isBordersShowedInitialized = false;

  if(isBordersShowed && !needShowTextBorders) {
    updateImage();
  }

  if(!isBordersShowed && needShowTextBorders && model_.currentPage().textBlocksNumber()) {
    imageWidget_->showImage( model_.currentPage().borderedTextImage() );
  }

  if(!isBordersShowedInitialized) {
    isBordersShowed = needShowTextBorders;
    isBordersShowedInitialized = true;
  }

  isBordersShowed = needShowTextBorders;
}

