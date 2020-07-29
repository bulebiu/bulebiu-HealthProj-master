#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QDebug>
#include <QtNetwork/QHostAddress>
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>

class TCPSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TCPSocket(QObject *parent = nullptr);

    // 连接到服务器
    bool connectToServer(QString strIp, quint16 port);

    // 发送数据

public slots:
    // 接收数据
    void receiveMessage();
    bool SendMessage(QByteArray content);
    void testTCPIP(QString ip, quint16 port);

signals:
    void dealMessage(QByteArray content);
    void testFailed();
    void testSuccess();

};

#endif // TCPSOCKET_H
