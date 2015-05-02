#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    //���������� ����
    int x,y;
    //��� ������� ������ ����
    Qt::MouseButton mbut;

    explicit CustomButton(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void Mouse_ButPressed();

public slots:

};

#endif // CUSTOMBUTTON_H
