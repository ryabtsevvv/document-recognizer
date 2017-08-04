// coding: utf-8
//! \file model/document_recognizer_model.hpp
//! \brief Бизнес-логика приложения.
//! \author Рябцев В.В.

#if !defined(_DOCUMENT_RECOGNIZER_MODEL_DOCUMENT_RECOGNIZER_MODEL_HPP)
#define _DOCUMENT_RECOGNIZER_MODEL_DOCUMENT_RECOGNIZER_MODEL_HPP

#include <QObject>

#include <documents/page_image.hpp>

class QString;

//! Основной класс бизнес-логики приложения.
//! Через данный класс осуществляется взаимодействие между обрабатываемыми данными
//! и графическим интерфейсом пользователя.
class DocumentRecognizerModel: public QObject {

    Q_OBJECT

public:

  //! Загружает изображение из файла.
  bool loadImage(const QString& fileName);

  //! Возвращает текущую обрабатываемую страницу документа.
  const PageImage& currentPage() const;

signals:

  //! Вызывается при успешной загрузке изображения из файла.
  void imageLoaded(const QString& fileName);

  //! Вызывается при неудачной загрузке изображения из файла.
  void imageLoadingFailed(const QString& fileName);

private:

  PageImage currentPage_;

}; // class DocumentRecognizerModel

inline
const PageImage& DocumentRecognizerModel::currentPage() const {
  return currentPage_;
}

#endif // _DOCUMENT_RECOGNIZER_MODEL_DOCUMENT_RECOGNIZER_MODEL_HPP
