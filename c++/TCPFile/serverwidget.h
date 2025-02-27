#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();
    void sendData();

private slots:
    void on_file_clicked();

    void on_send_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    QTimer timer;
};
#endif // SERVERWIDGET_H
