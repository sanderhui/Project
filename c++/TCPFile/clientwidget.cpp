#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    isStart = true;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::readyRead,
    [=](){
        QByteArray buf = tcpSocket->readAll();
        if(true==isStart)
        {
            isStart = false;

            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;
            file.setFileName(fileName);
            bool isOk = file.open(QIODevice::WriteOnly);
            if(false==isOk)
            {
                qDebug()<<"write error";

            }
        }
        else
        {

            qint64 len = file.write(buf);
            recvSize +=len;
            if(recvSize == fileSize)
            {
                file.close();
                QMessageBox::information(this,"完成","文件接收完成");
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        }
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip),port);
}
