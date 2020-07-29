#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkInterface>
#include "TCPSocket.h"
#include <QTimer>
#include "PlotWidget.h"
#include "hrwidget.h"
#include "stwidget.h"
#include "nibpwidget.h"
#include "respwidget.h"
#include "co2widget.h"
#include "spo2widget.h"
#include "tempwidget.h"
#include "tempwidget.h"
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    QTimer *tcpSendTimer;
    TCPSocket *socket;
    QString ipAddr;
    quint16 port;
    QString facilityName;
    QString facilitySerialNum = QNetworkInterface::allInterfaces()[0].hardwareAddress().split(":").join("0");
    bool connected = false;
    int counterX = 1;

    HRWidget *hr;
    STWidget *st;
    NIBPWidget *nibp;
    SPO2Widget *spo2;

    TEMPWidget *temp;
    RESPWidget *resp;
    CO2Widget *co2;


public slots:
    void initALL();
    void setTCPIP(QString ip, quint16 mport);
    void TCPGetMessage(QByteArray ba);
    void sendTCPOthers();
    void sendTCPWaves(int flag, QList<int>& dataForTCP);

signals:
    void facilityIDchanged(QString id);
    void ecgDataSended();
    void spo2DataSended();
    void bpDataSended();
    void connectedChangedSig();
};

#endif // CLIENT_H
