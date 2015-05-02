#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent) :
    QPushButton(parent)
{
}

//��������� ������� �� ������� ������ ����
void CustomButton::mousePressEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    x = ev->globalPos().x();
    y = ev->globalPos().y();
    emit Mouse_ButPressed();
}

