#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QFile>
class receiver : public QWidget
{
    Q_OBJECT
public:
    explicit receiver(QWidget *parent = nullptr);


private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 receiveSize;
    bool isStart;
};

#endif // RECEIVER_H
