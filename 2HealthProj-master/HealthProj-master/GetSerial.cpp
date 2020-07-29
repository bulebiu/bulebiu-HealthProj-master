#include "GetSerial.h"

GetSerial::GetSerial(QString portName_, QObject *parent) : QSerialPort(parent), portName(portName_)
{
}

QList<QString> GetSerial::getPortsName()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator iPort;
    QList<QString> portsName;
    for(iPort=ports.begin();iPort<ports.end();iPort++)
    {
        portsName.append(iPort->portName());
    }
    return portsName;
}

void GetSerial::connectPort()
{
    this->setPortName(portName);
    if(!this->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(NULL, "串口错误", "串口连接失败，错误代码"+QString::number(this->error()));
        return;
    }
    this->setBaudRate(QSerialPort::Baud115200);
    this->setDataBits(QSerialPort::Data8);
    this->setFlowControl(QSerialPort::NoFlowControl);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    connect(this, &QSerialPort::readyRead, this, &GetSerial::readMessage);
}

void GetSerial::statusMachine(char data)
{
    char tempData = data & 0xff;
    char mask = data & 0x80;
    if(mask == 0x00)
    {
        status = 0;
    }
    switch(status)
    {
    case 0:
        if(tempData == 0x08)
        {
            status = 1;
            pkgType = data;
            pkgDataHead = 0x00;
            dataLength = 7;
        }
        else if(tempData >= 0x09 && tempData <= 0x1A)
        {
            status = 1;
            pkgType = data;
            pkgDataHead = 0x00;
            dataLength = 1;
        }
        break;
    case 1:
        pkgDataHead = tempData;
        pkgDataCnt = 0;
        status = 2;
        break;
    case 2:
        if(pkgType == 0x08)
        {
            tempData = tempData & 0x7f;
            tempData = tempData | (char)(((pkgDataHead >> pkgDataCnt) & 0x1) << 7);
            pkgData[pkgDataCnt] = tempData;
            pkgDataCnt += 1;
            if(pkgDataCnt >= 7)
            {
                status = 3;
            }
        }
        else if(pkgType >= 0x09 && pkgType <= 0x1A)
        {
            tempData = tempData & 0x7f;
            tempData = tempData | (char)((pkgDataHead & 0x1) << 7);
            pkgData[0] = (tempData);
            status = 3;
        }
        break;
    case 3:
        if(pkgType == 0x08) //ECG
        {
            //拼接
            pkgDataInt[0] = ((this->pkgData[0] << 8) | (unsigned int)(this->pkgData[1] & 0xff));
            pkgDataInt[1] = ((this->pkgData[2] << 8) | (unsigned int)(this->pkgData[3] & 0xff));
            pkgDataInt[2] = ((this->pkgData[4] << 8) | (unsigned int)(this->pkgData[5] & 0xff));
            if((char)(pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2]) == (tempData & 0x7f)) //校验
            {
                dataForSending = (pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2])/3;
                if(flagCount == 0) //压缩
                {
                  emit receivedECGdata(dataForSending);
                  qDebug()<<(pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2])/3;
                  flagCount = 1;
                }
                flagCount --;
                //flagCount++;
                //if(flagCount==flagCountMax)
                //    flagCount = 0;
                //qDebug()<<pkgDataInt[0];
                //qDebug()<<pkgDataInt[1];
                //qDebug()<<pkgDataInt[2];
            }

        }
        else if(pkgType >= 0x09 && pkgType <= 0x1A)
        {
            pkgDataInt[0] = ((unsigned int)(pkgData[0] & 0xff));
            if(((char)(pkgDataInt[0] | 0x80)) == (char)tempData)
            {
                dataForSending = pkgDataInt[0];
                if(pkgType == 0x09)
                    emit receivedSPO2data(dataForSending);
                if(pkgType == 0x0a)
                    emit receivedBPdata(dataForSending);
                if(pkgType == 0x0b)
                    emit receivedHRdata(dataForSending);
                if(pkgType == 0x0c)
                    emit receivedST1data(dataForSending);
                if(pkgType == 0x0d)
                    emit receivedST2data(dataForSending);
                if(pkgType == 0x0e)
                    emit receivedPVCdata(dataForSending);
                if(pkgType == 0x0f)
                    emit receivedLBPdata(dataForSending);
                if(pkgType == 0x10)
                    emit receivedHBPdata(dataForSending);
                if(pkgType == 0x11)
                    emit receivedIBPdata(dataForSending);
                if(pkgType == 0x12)
                    emit receivedSPO2Wdata(dataForSending);
                if(pkgType == 0x13)
                    emit receivedBPMdata(dataForSending);
                if(pkgType == 0x14)
                    emit receivedT1data(dataForSending);
                if(pkgType == 0x15)
                    emit receivedT2data(dataForSending);
                if(pkgType == 0x16)
                    emit receivedTDdata(dataForSending);
                if(pkgType == 0x17)
                    emit receivedRESPdata(dataForSending);
                if(pkgType == 0x18)
                    emit receivedCO2data(dataForSending);
                if(pkgType == 0x19)
                    emit receivedAWRRdata(dataForSending);
                if(pkgType == 0x1a)
                    emit receivedINSdata(dataForSending);
            }
        }
        status = 0;
        pkgData[0] = 0;
        pkgData[1] = 0;
        pkgData[2] = 0;
        pkgData[3] = 0;
        pkgData[4] = 0;
        pkgData[5] = 0;
        pkgData[6] = 0;
        pkgDataInt[0] = 0;
        pkgDataInt[1] = 0;
        pkgDataInt[2] = 0;
        break;
    default:
        break;
    }
}

//bool GetSerial::sendString(QString str)
//{
//    if(comPort->write(str.toStdString().c_str()))
//        return true;
//    else
//        return false;
//}

/*void GetSerial::readMessage()
{
    QByteArray data;
    data = this->read(1);
    statusMachine(data[0]);
    if (this->bytesAvailable()>0)
    {
        readMessage();
    }
}*/

void GetSerial::readMessage()
{
    QByteArray data;
    // 读取串口数据
    data = this->read(1);
    rxDataHandle(data[0]);
    if (status == 4)
    {
        // 发信号通知画波形
        //dataForSending = (ecg1+ecg2+ecg3)/3;
        dataForSending = ecg1;
        if(flagCount == 0) //压缩
        {
          emit receivedECGdata(dataForSending);
          qDebug()<<dataForSending;
          flagCount = 1;
        }
        flagCount --;
    }
    if (this->bytesAvailable()>0)
    {
        readMessage();
    }
}

void GetSerial::rxDataHandle(char data)
{
    // 状态机
    // 状态0： 空闲，接收到包类型ID 0x08后进入状态1
    // 状态1： 已经接收到数据包类型ID，接收数据包头，进入下一个状态。
    // 状态2： 数据接收状态， 用数据头中相应位填补接收数据的高位，并且缓存数据，
    //        接收满特定长度的数据后，进入下一个状态
    // 状态3： 数据校验，接收校验字节，并且进行校验
    // 状态4： 结束

    char dataTmp;
    data = data&0xff;
    int datamask = data&0x80;
    if (datamask == 0x00)
    {
        // 最高位为0，该数据是包类型ID
        this->status = 0;
    }
    switch (this->status)
    {
    case 0:
        if (data == 0x08) // ECG
        {
            this->status = 1;       // 状态切换
            this->pkgType = data;   // 保存包类型
            this->pkgDataHead = 0;  // 清空，为接收头部字节做准备
            this->dataLength = 7;   // 数据长度
        }
        else
        {
            qDebug() << "unknow pkgType";
        }
        break;
    case 1:
        this->pkgDataHead = data;
        this->pkgDataCnt = 0;
        this->status = 2;
        break;
    case 2:   // 接收数据
        dataTmp = data & 0x7f;  // 保留数据的低7位

        // 第一个数据的最高位，在数据头的最低位中
        dataTmp = dataTmp | (((this->pkgDataHead >> this->pkgDataCnt) & 0x1) << 7);
        this->pkgData[pkgDataCnt] = dataTmp; // 保存解析后的数据
        this->pkgDataBuf[pkgDataCnt] = data;  // 保存解析前的数据
        pkgDataCnt += 1;

        // 根据协议我们知道数据数据长度为7
        if (pkgDataCnt >= 7)
        {
            status = 3;
        }
        break;
    case 3:
        // 校验

        // 得到ecg数据
        ecg1 = this->pkgData[0];
        ecg1 = (ecg1 << 8);
        ecg1 = ecg1 | this->pkgData[1];

        ecg2 = this->pkgData[2];
        ecg2 = (ecg2 << 8) | this->pkgData[3];

        ecg3 = this->pkgData[4];
        ecg3 = (ecg3 << 8) | this->pkgData[5];
        // 测试
        //qDebug() << ecg1;
        //qDebug() << ecg2;
        //qDebug() << ecg3;

        this->status = 4;
        break;
    default:
        break;
    }
}
