#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QScrollBar>
#include <QTimer>
#include <qdesktopwidget.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Центрирование экрана
    QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
    //Установить фильтр на события к окну
    qApp->installEventFilter(this);
    eventString = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Сохранение данных по событиям в текстовый файл
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName();
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) return;
    QTextStream out(&file);
    out << eventString;
    file.close();
}
//Слушатель события по нажатию кнопки мыши
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    emit Mouse_ButPressed();
}
//Слушатель события по двойному нажатию кнопки мыши
void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    emit Mouse_DButPressed();
}
//Слушатель события по отпусканию кнопки мыши
void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Released();
}
//Обработчик события по нажатию кнопки мыши
void MainWindow::Mouse_ButPressed()
{
    eventString += "Mouse press button: " + QString::number(this->mbut) + "\n";
    alignText(eventString);
}
//Обработчик события по двойному нажатию кнопки мыши
void MainWindow::Mouse_DButPressed()
{
    eventString += "Mouse double press button: " + QString::number(this->mbut) + "\n";
    alignText(eventString);
}
//Обработчик события по отпусканию кнопки мыши
void MainWindow::Mouse_Released()
{
    eventString += "Mouse released\n";
    alignText(eventString);
}
//Обработчик события по нажатию кнопки клавиатуры
void MainWindow::Key_Pressed()
{
    eventString += "Keyboard press button: " + QString::number(this->key) + "\n";
    alignText(eventString);
}
//Обработчик события по отпусканию кнопки клавиатуры
void MainWindow::Key_Released()
{
    eventString += "Keyboard released\n";
    alignText(eventString);
}
//Слушатель события по нажатию кнопки клавиатуры
void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    this->key = ev->key();
    emit Key_Pressed();
}
//Слушатель события по отпусканию кнопки клавиатуры
void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    emit Key_Released();
}
//Фильтр событий (фильтруем событие по движению мыши)
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    this->x = mouseEvent->globalPos().x();
    this->y = mouseEvent->globalPos().y();
  }
  return false;
}
//Автоскрол текста
void MainWindow::alignText(QString strText)
{
        ui->txtShow->insertPlainText(strText);
        QTextCursor c = ui->txtShow->textCursor();
        c.movePosition(QTextCursor::End);
        ui->txtShow->setTextCursor(c);
}
void MainWindow::updateCaption()
{
        eventString += "Mouse move x: " + QString::number(this->x) + " y: " + QString::number(this->y) + "\n";
        alignText(eventString);
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox msg;
    msg.setText("Button2");
    msg.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msg;
    msg.setText("Button1");
    msg.exec();
}

CustomButton* MainWindow::getButton1()
{
    return ui->pushButton_2;
}
CustomButton* MainWindow::getButton2()
{
    return ui->pushButton_3;
}
