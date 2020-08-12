#include "widget.h"
#include"receiver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //发送文件
    //Widget w;
    //w.show();
    //接受文件
    receiver r;

    return a.exec();
}
