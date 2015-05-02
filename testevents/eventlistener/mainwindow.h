#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include "custombutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
    
public:
    //Строка со списком событий
    QString eventString;
    //Код нажатой кнопки клавиатуры
    int key;
    //Код нажатой кнопки мыши
    Qt::MouseButton mbut;
    //Координаты мыши
    int x,y;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    bool eventFilter(QObject *obj, QEvent *event);
    void alignText(QString text);
    void updateCaption();
    CustomButton *getButton1();
    CustomButton *getButton2();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void Mouse_ButPressed();
    void Mouse_DButPressed();
    void Mouse_Released();
    void Key_Pressed();
    void Key_Released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
