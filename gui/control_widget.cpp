#include <QCheckBox>
#include <QGridLayout>
#include "control_widget.hpp"

ControlWidget::ControlWidget(QWidget *parent):
  QWidget(parent),
  showTextBordersCheckBox_( new QCheckBox(tr("Отобразить границы текста"), this) ),
  layout_(new QGridLayout(this))
{
  layout_->addWidget(showTextBordersCheckBox_, 0, 0);
  layout_->setAlignment(showTextBordersCheckBox_, Qt::AlignTop);
  //setLayout(layout_);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  adjustSize();
  connectSignalsAndSlots();
}

bool ControlWidget::isShowTextBorderCheckBoxChecked() const
{
  return showTextBordersCheckBox_->isChecked();
}


void ControlWidget::connectSignalsAndSlots()
{
  connect( showTextBordersCheckBox_, SIGNAL( stateChanged(int) ), this, SLOT( checkNewStateForShowTextBordersCheckBox() ) );
}

void ControlWidget::checkNewStateForShowTextBordersCheckBox()
{
  emit showTextBordersCheckBoxChecked( showTextBordersCheckBox_->isChecked() );
}

