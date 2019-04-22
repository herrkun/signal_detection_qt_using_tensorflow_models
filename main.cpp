#include "dialog.h"
#include <QApplication>

/***
 * 2019.1.09 已经开了另外一个线程，解决打开mat文件出现thread错误的问题，
 * 原有的程序在runpy（）函数中，为了测试并对比并未去除，后期要去掉
 *多线程和单线程之间的切换依靠是否打开和关闭 model->start();来实现
 *
***/

QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QVector<QPointF> >("QVector<QPointF>");

    Dialog w;
    w.show();

    return a.exec();
}
