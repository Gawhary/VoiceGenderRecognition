#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

//#include "vectorutils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

//    QVector<double> x;
//    x << 10 << 20 << 30 << 40 << 50 << 60 << 70 << 80 << 90 << 100;

//    QVector<double> y;
//    y << 10 << 9 << 8 << 7 << 6 << 5 << 4 << 3 << 2 << 1;

//    QVector<double> z1 = vector::conv(x, y);
//    qDebug() << z1;

//    qDebug() << vector::xcorr(x, y);
//    qDebug() << vector::xcorr(x, y, true);
//    qDebug() << "-----------------------";
//    qDebug() << vector::xcorr(x, y, 4);
//    qDebug() << vector::xcorr(x, y, 4, true);
//    qDebug() << "-----------------------";
//    qDebug() << vector::xcorr(x);
//    qDebug() << vector::xcorr(x, true);
//    qDebug() << "-----------------------";
//    qDebug() << vector::xcorr(x, 4);
//    qDebug() << vector::xcorr(x, 4, true);
//    qDebug() << "-----------------------";

//    return 0;
}
