#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QScreen>
#include <QGuiApplication>

#include "PlotWidget.h"
#include "plotwidget2.h"
#include "plotwidget3.h"

#include "GetSerial.h"
#include "titlebar.h"
#include "hrwidget.h"
#include "stwidget.h"
#include "nibpwidget.h"
#include "respwidget.h"
#include "co2widget.h"
#include "spo2widget.h"
#include "tempwidget.h"
#include "TCPSocket.h"
#include "client.h"


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;

    //注意：由于Qt对象树在销毁时，含有子对象且在栈区的对象，销毁时会把子对象也销毁
    //     而子对象还会销毁一遍，这样就出错了，会无法退出，因此这里指用针将其放在堆区
    //布局Layout
    QVBoxLayout *splitTitle = new QVBoxLayout;
    QVBoxLayout *leftPlotsLayout = new QVBoxLayout;
    QHBoxLayout *leftrightLayout = new QHBoxLayout;
    QGridLayout *rightGrids = new QGridLayout;

    //布局Widget
    QWidget *left = new QWidget(this);
    QWidget *right = new QWidget(this);
    QWidget *mainW = new QWidget(this);

    //待提升的Widget
    TitleBar title;
    PlotWidget ecgiiPlot;
    PlotWidget2 spo2Plot;
    PlotWidget3 bpPlot;

    HRWidget hr;
    STWidget st;
    NIBPWidget nibp;
    SPO2Widget spo2;

    TEMPWidget temp;
    RESPWidget resp;
    CO2Widget co2;

    GetSerial *gs = new GetSerial();

    Client cl;
    QThread tcpThread;
    //QTimer tcpTimer;

    QString patientName;
    QString patientSex;
    QString patientAge;
    QString patientID;

    //测试区

public slots:
    void setFull();
    void setNotFull();
signals:
    void initTCPSig();
};
#endif // MAINWIDGET_H
