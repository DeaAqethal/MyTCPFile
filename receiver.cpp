#include "receiver.h"

receiver::receiver(QWidget *parent) : QWidget(parent)
{
    isStart = true;
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    connect(tcpServer,&QTcpServer::newConnection,
    [=]
    {
       tcpSocket = tcpServer->nextPendingConnection();
       QString ip = tcpSocket->peerAddress().toString();
       quint16 port = tcpSocket->peerPort();
       QString str = QString("[%1:%2]成功连接").arg(ip).arg(port);
       qDebug()<<str;
       connect(tcpSocket,&QTcpSocket::readyRead,
               [=]
               {
                   QByteArray buf = tcpSocket->readAll();

                   if(true == isStart)
                   {
                       isStart = false;

                       fileName = QString(buf).section("##",0,0);
                       fileSize = QString(buf).section("##",1,1).toInt();
                       receiveSize = 0;

                       file.setFileName(fileName);

                       bool isOk = file.open(QIODevice::WriteOnly);
                       if(isOk == false)
                       {
                           qDebug()<<"只读方式打开出错";
                       }
                   }
                   else
                   {
                       qint64 len = file.write(buf);
                       receiveSize +=len;
                       if(receiveSize==fileSize)
                       {
                           file.close();
                           qDebug()<<"传输完成";
                           isStart = true;

                       }
                   }
               }
               );

    });

}
