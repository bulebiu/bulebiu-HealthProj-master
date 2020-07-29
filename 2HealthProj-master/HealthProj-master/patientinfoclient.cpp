#include "patientinfoclient.h"

patientInfoClient::patientInfoClient(QObject *parent) : QObject(parent)
{

}

void patientInfoClient::getinfo()
{
    if(mdeviceID.isEmpty())
        return;
    socket = new TCPSocket;
    connect(socket, &TCPSocket::dealMessage, this, &patientInfoClient::readinfo);
    if(socket->connectToServer(ipAddr, port))
        socket->SendMessage(QString("getPatientInfo,%1;").arg(mdeviceID).toUtf8());
}

void patientInfoClient::readinfo(QByteArray ba)
{
    QString dataStr = QString(ba).split(";")[0];
    QStringList dataList = dataStr.split(",");
    emit sendInfo2Widget(dataList[2], dataList[3], dataList[4], dataList[1]);
}
