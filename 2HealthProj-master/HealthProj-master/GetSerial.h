#ifndef GETSERIAL_H
#define GETSERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include "PlotWidget.h"

class GetSerial : public QSerialPort
{
    Q_OBJECT
public:
    explicit GetSerial(QString portName_ = "COM1", QObject *parent = nullptr);
    QString portName;
    QList<QString> getPortsName();
    void connectPort();

private:
    void statusMachine(char data);
    int status;
    //char pkgType;
    //char pkgDataHead;
    int dataLength;
    //int pkgDataCnt;
    //char pkgData[10];
    int pkgDataInt[3];
    unsigned int dataForSending;

    int flagCount = 2;
    unsigned char pkgType;     // 包类型ID
    unsigned char pkgDataHead;     // 头部
    unsigned char pkgDataBuf[10];  // 数据包最大为10个字节，解析前
    unsigned char pkgData[10];     // 解析后
    unsigned int pkgDataCnt;       // 接收的数据个数
    unsigned int ecg1, ecg2, ecg3;
    void rxDataHandle(char data);
public slots:
    //bool sendString(QString str);
    void readMessage();
signals:
    //void receivedData(QString nowdata);
    void receivedECGdata(int data);
    void receivedBPdata(int data);
    void receivedSPO2data(int data);

    void receivedHRdata(int data);

    void receivedST1data(int data);
    void receivedST2data(int data);
    void receivedPVCdata(int data);

    void receivedLBPdata(int data);
    void receivedHBPdata(int data);
    void receivedIBPdata(int data);

    void receivedSPO2Wdata(int data);
    void receivedBPMdata(int data);

    void receivedT1data(int data);
    void receivedT2data(int data);
    void receivedTDdata(int data);

    void receivedRESPdata(int data);

    void receivedCO2data(int data);
    void receivedAWRRdata(int data);
    void receivedINSdata(int data);

};

#endif // GETSERIAL_H
