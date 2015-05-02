#include "custombutton.h"
#include <QMessageBox>

CustomButton::CustomButton(QWidget *parent) :
    QPushButton(parent)
{
}

//Слушатель события по нажатию кнопки мыши
void CustomButton::mousePressEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    x = ev->globalPos().x();
    y = ev->globalPos().y();
    Mouse_ButPressed();
}

void CustomButton::Mouse_ButPressed()
{
    QMessageBox msg;
    msg.setText("Button: " + QString::number(mbut));
    msg.exec();
}
