#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_connect_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket;

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;
    bool isStart;
};

#endif // CLIENTWIDGET_H
