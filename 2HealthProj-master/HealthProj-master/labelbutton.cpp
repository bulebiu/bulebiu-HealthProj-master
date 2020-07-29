#include "labelbutton.h"

LabelButton::LabelButton(QWidget *parent) : QLabel(parent)
{

}

void LabelButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    this->setStyleSheet("background-color: black;");
}

void LabelButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->setStyleSheet("background-color: rgb(87, 96, 111);");
    emit clicked();
}

void LabelButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setStyleSheet("background-color: rgb(87, 96, 111);");
}

void LabelButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setStyleSheet("");
}
