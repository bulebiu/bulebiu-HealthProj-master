#ifndef TCPSETTINGSWIDGET_H
#define TCPSETTINGSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QThread>
#include "TCPSocket.h"

class TCPSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TCPSettingsWidget(QWidget *parent = nullptr);
    void setWindowSize(int w, int h);
    QVBoxLayout *all = new QVBoxLayout;
    QHBoxLayout *ipLayout = new QHBoxLayout;
    QHBoxLayout *portLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *applyBtn = new QPushButton;
    QPushButton *testBtn = new QPushButton;
    QLabel *ipLabel = new QLabel;
    QLabel *portLabel = new QLabel;
    QLineEdit *ipEdit = new QLineEdit;
    QLineEdit *portEdit = new QLineEdit;

    TCPSocket *socketForTest = new TCPSocket;

    QThread thread;


public slots:
    void setTCPIP();
    void testTCPIP();
    void successTest();
    void failTest();

signals:
    void tcpipChanged(QString ip, quint16 port);
    void testSig(QString ip, quint16 port);

};

#endif // TCPSETTINGSWIDGET_H
