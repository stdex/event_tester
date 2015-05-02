#include <QApplication>
#include <QTest>
#include "mainwindow.h"
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>

int main(int argc, char *argv[])
{
    int x = 0, y = 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString eventString;
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return 0;
    QTextStream in(&file);
    eventString = in.readAll();
    QStringList myList = eventString.split("\n");

    for(int i=0; i<myList.size(); i++ )
    {
        QString line = myList.at(i);
        if(line.indexOf("x:")!=-1)//Координаты мыши
        {
            x = line.mid(line.indexOf("x:")+2,(line.indexOf("y:")-line.indexOf("x:")-2)).trimmed().toInt();
            y = line.mid(line.indexOf("y:")+2).trimmed().toInt();
            QTest::mouseMove(&w,QPoint(x-w.pos().x()-4,y-w.pos().y()-30),100);
            w.updateCaption();
        }
        if(line.indexOf("Mouse press button:")!=-1)
        {
            int num = line.mid(line.indexOf("Mouse press button:")+19).trimmed().toInt();
            if((x>=w.getButton1()->pos().x()+w.pos().x()-4 )&&(y>=w.getButton1()->pos().y()+w.pos().y() )&&
               (x<=w.getButton1()->pos().x()+w.getButton1()->width()+w.pos().x()+4 )&&(y<=w.getButton1()->pos().y()+w.getButton1()->height()+w.pos().y()+35))
            {
                QTest :: mouseClick ( w.getButton1(), Qt::MouseButton(num), 0, QPoint ( ), 2500 );
            }
            else if((x>=w.getButton2()->pos().x()+w.pos().x()-4 )&&(y>=w.getButton2()->pos().y()+w.pos().y() )&&
               (x<=w.getButton2()->pos().x()+w.getButton2()->width()+w.pos().x()+4 )&&(y<=w.getButton2()->pos().y()+w.getButton2()->height()+w.pos().y()+35))
            {
                QTest :: mouseClick ( w.getButton2(), Qt::MouseButton(num), 0, QPoint ( ), 2500 );
            }
            else
            {
                QTest::mousePress(&w,Qt::MouseButton(num));
            }
        }
        if(line.indexOf("Mouse double press button:")!=-1)
        {
            int num = line.mid(line.indexOf("Mouse double press button:")+26).trimmed().toInt();

            QTest::mousePress(&w,Qt::MouseButton(num));
        }
        if(line.indexOf("Mouse released")!=-1)
        {
            QTest::mouseRelease(&w,Qt::NoButton);
        }
        if(line.indexOf("Keyboard press button:")!=-1)
        {
            int num = line.mid(line.indexOf("Keyboard press button:")+22).trimmed().toInt();

            QTest::keyPress(&w,(char&)num);
        }
        if(line.indexOf("Keyboard released")!=-1)
        {
            QTest::keyRelease(&w,(char&)"d");
        }
        QTest::qSleep(1000);
    }
    file.close();
    return a.exec();
}
