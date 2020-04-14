#include "serverwidget.h"
#include "ui_serverwidget.h"



ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    //两个按钮不能按

    ui->file->setEnabled(false);
    ui->send->setEnabled(false);

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器端口为：8888");
    connect(tcpServer,&QTcpServer::newConnection,
    [=](){
        tcpSocket = tcpServer->nextPendingConnection();//取出连接的套接字
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();

        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        ui->textEdit->setText(str);
        ui->file->setEnabled(true);
    });
    connect(&timer,&QTimer::timeout,
            [=](){
        timer.stop();
        sendData();
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}
void ServerWidget::sendData()
{
    qint64 len = 0;
    do
    {
        char buf[4*1024] = {0};
        len=0;
        len = file.read(buf,sizeof(buf));
        len = tcpSocket->write(buf,len);
        sendSize +=len;

    }while(len>0);
    if (sendSize==fileSize)
    {

        ui->textEdit->append("文件发送完毕");
        file.close();
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
}

void ServerWidget::on_file_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(false==filePath.isEmpty())
    {
        fileName.clear();
        fileSize = 0;
        sendSize = 0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        file.setFileName(filePath);
        bool isOk = file.open(QIODevice::ReadOnly);
        if(false==isOk)
        {
            qDebug()<<"打开文件失败";
        }
        ui->textEdit->append(filePath);
        ui->file->setEnabled(false);
        ui->send->setEnabled(true);

    }
    else
    {
        qDebug()<<"选择文件路径出错 62";
    }
}

void ServerWidget::on_send_clicked()
{
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);

    qint64 len = tcpSocket->write(head.toUtf8());
    if(len>0)
    {
        qDebug()<<"点击发送";
        timer.start(20);
    }
    else
    {
        qDebug()<<"头部信息发送失败";
        file.close();
        ui->file->setEnabled(true);
        ui->send->setEnabled(false);

    }
}
