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
    //������������� ������
    QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
    //���������� ������ �� ������� � ����
    qApp->installEventFilter(this);
    eventString = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}
//���������� ������ �� �������� � ��������� ����
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName();
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) return;
    QTextStream out(&file);
    out << eventString;
    file.close();
}
//��������� ������� �� ������� ������ ����
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    emit Mouse_ButPressed();
}
//��������� ������� �� �������� ������� ������ ����
void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    this->mbut = ev->button();
    emit Mouse_DButPressed();
}
//��������� ������� �� ���������� ������ ����
void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Released();
}
//���������� ������� �� ������� ������ ����
void MainWindow::Mouse_ButPressed()
{
    eventString += "Mouse press button: " + QString::number(this->mbut) + "\n";
    alignText(eventString);
}
//���������� ������� �� �������� ������� ������ ����
void MainWindow::Mouse_DButPressed()
{
    eventString += "Mouse double press button: " + QString::number(this->mbut) + "\n";
    alignText(eventString);
}
//���������� ������� �� ���������� ������ ����
void MainWindow::Mouse_Released()
{
    eventString += "Mouse released\n";
    alignText(eventString);
}
//���������� ������� �� ������� ������ ����������
void MainWindow::Key_Pressed()
{
    eventString += "Keyboard press button: " + QString::number(this->key) + "\n";
    alignText(eventString);
}
//���������� ������� �� ���������� ������ ����������
void MainWindow::Key_Released()
{
    eventString += "Keyboard released\n";
    alignText(eventString);
}
//��������� ������� �� ������� ������ ����������
void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    this->key = ev->key();
    emit Key_Pressed();
}
//��������� ������� �� ���������� ������ ����������
void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    emit Key_Released();
}
//������ ������� (��������� ������� �� �������� ����)
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
//��������� ������
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
