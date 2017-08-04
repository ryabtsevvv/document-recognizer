// coding: utf-8
//! \file gui/control_widget.hpp
//! \brief Виджет, содержащий основные элементы управления приложением.
//! \author Рябцев В.В.

#if !defined(_FLARE_PROCESSING_GUI_CONTROL_WIDGET_HPP)
#define _FLARE_PROCESSING_GUI_CONTROL_WIDGET_HPP

#include <QWidget>

class QCheckBox;
class QGridLayout;

//! Класс, определяющий виджет, содержащий основные элементы управления приложением
//! и являющийся dock-виджетом основного окна приложения.
class ControlWidget: public QWidget {

  Q_OBJECT

public:

  ControlWidget(QWidget * parent = nullptr);

  //! Возвращает признак выбора отображения рамок вокруг предполагаемых текстовых блоков.
  bool isShowTextBorderCheckBoxChecked() const;

signals:

  void showTextBordersCheckBoxChecked(bool);

private slots:

  void checkNewStateForShowTextBordersCheckBox();

private:

  void connectSignalsAndSlots();

  QCheckBox * showTextBordersCheckBox_;
  QGridLayout * layout_;

}; // class ControlWidget

#endif // _FLARE_PROCESSING_GUI_CONTROL_WIDGET_HPP
