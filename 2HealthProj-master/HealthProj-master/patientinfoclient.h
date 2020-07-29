#ifndef PATIENTINFOCLIENT_H
#define PATIENTINFOCLIENT_H

#include <QObject>
#include "TCPSocket.h"

class patientInfoClient : public QObject
{
    Q_OBJECT
public:
    explicit patientInfoClient(QObject *parent = nullptr);
    TCPSocket *socket;
    QString ipAddr;
    quint16 port;
    QString mdeviceID;

signals:
    void sendInfo2Widget(QString name, QString sex, QString age, QString idNum);

public slots:
    void getinfo();
    void readinfo(QByteArray ba);
};

#endif // PATIENTINFOCLIENT_H
