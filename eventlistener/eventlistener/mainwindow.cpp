#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QScrollBar>
#include <QTimer>
#include <QMessageBox>
#include <qdesktopwidget.h>
#include "custombutton.h"


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
    this->x = 0;
    this->y = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(1000);
    connect(ui->pushButton_2, SIGNAL(Mouse_ButPressed()), this, SLOT(ButtonMouse_ButPressed1()));
    connect(ui->pushButton_3, SIGNAL(Mouse_ButPressed()), this, SLOT(ButtonMouse_ButPressed2()));
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

//���������� ������� �� ������� ������ ����
void MainWindow::ButtonMouse_ButPressed1()
{
    eventString += "Mouse move x: " + QString::number(ui->pushButton_2->x) + " y: " + QString::number(ui->pushButton_2->y) + "\n";
    eventString += "Mouse press button: " + QString::number(ui->pushButton_2->mbut) + "\n";
    alignText(eventString);
}
//���������� ������� �� ������� ������ ����
void MainWindow::ButtonMouse_ButPressed2()
{
    eventString += "Mouse move x: " + QString::number(ui->pushButton_3->x) + " y: " + QString::number(ui->pushButton_3->y) + "\n";
    eventString += "Mouse press button: " + QString::number(ui->pushButton_3->mbut) + "\n";
    alignText(eventString);
}

