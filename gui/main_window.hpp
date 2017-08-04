#if !defined(_DOCUMENT_RECOGNIZER_GUI_MAIN_WINDOW_HPP)
#define _DOCUMENT_RECOGNIZER_IMAGE_IMAGE_HPP

#include <QMainWindow>

// Предварительные объявления классов

namespace Ui {  class DocumentRecognizerMainWindow; }
class ControlWidget;
class ImageWidget;
class DocumentRecognizerModel;

//! Класс, реализующий основное окно приложения.
class DocumentRecognizerMainWindow: public QMainWindow {

  Q_OBJECT

public:

  DocumentRecognizerMainWindow(DocumentRecognizerModel& model, QWidget * parent = nullptr);

  ~DocumentRecognizerMainWindow();

public slots:

  void openFile();
  void updateImage();
  void updateImage(const QString& fileName);
  void showImageLoadingFailedDialog(const QString& fileName);
  void showTextBorders(bool needShowTextBorders);

private:

  DocumentRecognizerModel& model_;            //!< Модель бизнес-логики приложения.

  Ui::DocumentRecognizerMainWindow * ui_;     //!< Автоматически генерируемый графический интерфейс пользователя.
  ControlWidget * controlWidget_;             //!< Виджет, содержаший основные элементы управления программой.
  ImageWidget * imageWidget_;               //!< Виджет, отвечающий за вывод на экрас изображений в формате OpenCV.

  QString lastUsedDirectory_;                 //!< Последняя папка, из которой считывались изображения.

private:

  void connectSignalsAndSlots();

}; // class FlareProcessing

#endif // _DOCUMENT_RECOGNIZER_IMAGE_IMAGE_HPP
