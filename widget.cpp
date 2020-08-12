#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QDebug>
#include<QFileInfo>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost("127.0.0.1",8888);

    connect(&timer,&QTimer::timeout,
            [=]
    {
       timer.stop();

       sendData();
    });

}
void Widget::sendData()
{
    qint64 len = 0;
    do
    {
        char buf[4*1024] = {0};
        len = 0;

        len = file.read(buf,sizeof(buf));

        len = tcpSocket->write(buf,len);

        sendSize += len;

    }while(len>0);

    if(sendSize == fileSize){
        ui->textEdit->append("文件发送完毕");
        file.close();


    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(false == filePath.isEmpty()){
        fileName.clear();
        fileSize = 0;

        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        sendSize = 0;

        file.setFileName(filePath);

        bool isOk = file.open(QIODevice::ReadOnly);
        if(isOk == false){
            qDebug()<<"只读方式打开文件失败 55";
        }
        ui->textEdit->setText(filePath);
    }
    else{
        qDebug() << "选择文件出错";
    }

}

void Widget::on_buttonSend_clicked()
{
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8());
    qDebug()<<len;
    if(len>0){
        timer.start(20);
    }
    else{
        qDebug()<<"头部信息发送失败";
        file.close();
        ui->buttonFile->setEnabled(true);
        ui->buttonSend->setEnabled(false);
    }
}
