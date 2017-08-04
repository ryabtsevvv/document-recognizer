// coding: utf-8
//! \file image/recognizable_object.hpp
//! \brief Реализация концепции "Распознаваемый объект".
//! \author Рябцев В.В.

#if !defined(_DOCUMENT_RECOGNIZER_RECOGNIZABLE_OBJECT_HPP)
#define _DOCUMENT_RECOGNIZER_RECOGNIZABLE_OBJECT_HPP

//! Класс, реализующий концепцию распознаваемого объекта.
//! Все классы объектов, подлежащих распознаванию должны быть унаследованы от данного класса.
class RecognizableObject {
public:

  //! Состояние распознаваемого объекта.
  enum class State {
    New,              //!< Состояние вновь созданного объекта, к которому не применялась процедура распознавания.
    Recognized,       //!< Состояние успешно распознанного объекта.
    Unrecognized      //!< Состояние, соответствующее объекту, который не был распознан.
  };

  //! Конструктор.
  RecognizableObject();

  //! Деструктор.
  virtual ~RecognizableObject() {}

  //! Возвращает признак распознанного объекта.
  virtual bool isRecognized() const;

  //! Возвращает признак нераспознанного объекта.
  virtual bool isUnrecognized() const;

  //! Возвращает состояние распознаваемого объекта.
  State state() const;

protected:
  State state_;     //!< Состояние распознаваемого объекта.
};

inline
RecognizableObject::State RecognizableObject::state() const {
  return state_;
}

#endif // _DOCUMENT_RECOGNIZER_RECOGNIZABLE_OBJECT_HPP
