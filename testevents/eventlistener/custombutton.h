#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    //Координаты мыши
    int x,y;
    //Код нажатой кнопки мыши
    Qt::MouseButton mbut;

    explicit CustomButton(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
    void Mouse_ButPressed();
signals:


public slots:

};

#endif // CUSTOMBUTTON_H
