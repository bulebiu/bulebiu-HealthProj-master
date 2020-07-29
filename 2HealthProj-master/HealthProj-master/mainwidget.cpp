#include "mainwidget.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //this->setWindowFlag(Qt::FramelessWindowHint);
    QScreen* screen = QGuiApplication::screens().at(0);
    QRect screenRect = screen->availableGeometry();
    this->resize(screenRect.width()*2/3, screenRect.height()*2/3);

    title.setFixedHeight(50);
    title.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    splitTitle->addWidget(&title);
    splitTitle->addWidget(mainW);
    splitTitle->setMargin(0);
    splitTitle->setSpacing(1);

    title.setStyleSheet("background-color: rgb(47, 53, 66)");
    mainW->setStyleSheet("background-color: white");
    ecgiiPlot.setStyleSheet("background-color: rgb(47, 53, 66)");
    spo2Plot.setStyleSheet("background-color: rgb(47, 53, 66)");
    bpPlot.setStyleSheet("background-color: rgb(47, 53, 66)");
    hr.setStyleSheet("background-color: rgb(47, 53, 66)");
    st.setStyleSheet("background-color: rgb(47, 53, 66)");
    nibp.setStyleSheet("background-color: rgb(47, 53, 66)");
    spo2.setStyleSheet("background-color: rgb(47, 53, 66)");
    temp.setStyleSheet("background-color: rgb(47, 53, 66)");
    resp.setStyleSheet("background-color: rgb(47, 53, 66)");
    co2.setStyleSheet("background-color: rgb(47, 53, 66)");

    leftrightLayout->addWidget(left);
    leftrightLayout->addWidget(right);
    leftrightLayout->setStretch(0, 2);
    leftrightLayout->setStretch(1, 1);
    leftrightLayout->setMargin(0);
    leftrightLayout->setSpacing(1);
    leftPlotsLayout->addWidget(&ecgiiPlot);
    leftPlotsLayout->addWidget(&spo2Plot);
    leftPlotsLayout->addWidget(&bpPlot);
    leftPlotsLayout->setMargin(0);
    leftPlotsLayout->setSpacing(1);

    rightGrids->addWidget(&hr,0, 0, 1, 1);
    rightGrids->addWidget(&st,0, 1, 1, 1);
    rightGrids->addWidget(&nibp,1, 0, 1, 2);
    rightGrids->addWidget(&spo2,2, 0, 1, 1);
    rightGrids->addWidget(&temp,2, 1, 1, 1);
    rightGrids->addWidget(&resp,3, 0, 1, 1);
    rightGrids->addWidget(&co2,3, 1, 1, 1);
    rightGrids->setMargin(0);
    rightGrids->setSpacing(1);
    rightGrids->setRowStretch(0, 1);
    rightGrids->setRowStretch(1, 1);
    rightGrids->setRowStretch(2, 1);
    rightGrids->setRowStretch(3, 1);
    rightGrids->setColumnStretch(1, 1);
    rightGrids->setColumnStretch(0, 1);

    left->setLayout(leftPlotsLayout);
    right->setLayout(rightGrids);
    mainW->setLayout(leftrightLayout);

    this->setLayout(splitTitle);

    connect(&title, &TitleBar::enablefullscreen, this, &MainWidget::setFull);
    connect(&title, &TitleBar::disablefullscreen, this, &MainWidget::setNotFull);

    //测试区
    ecgiiPlot.y0 = 0;
    ecgiiPlot.yScale = 4096;
    ecgiiPlot.xScale = 1000;
    ecgiiPlot.updateInterval = 1;
    ecgiiPlot.color = Qt::green;
    ecgiiPlot.text = "ECG";
    ecgiiPlot.plotflag = 1;

    spo2Plot.y0 = 0;
    spo2Plot.yScale = 300;
    spo2Plot.xScale = 1000;
    spo2Plot.updateInterval = 1;
    spo2Plot.color = Qt::red;
    spo2Plot.text = "SPO2";
    spo2Plot.plotflag = 2;

    bpPlot.y0 = 0;
    bpPlot.yScale = 300;
    bpPlot.xScale = 1000;
    bpPlot.updateInterval = 1;
    bpPlot.color = Qt::yellow;
    bpPlot.text = "BP";
    bpPlot.plotflag = 3;

    connect(gs, &GetSerial::receivedECGdata, &ecgiiPlot, &PlotWidget::sendData);
    connect(gs, &GetSerial::receivedBPdata, &bpPlot, &PlotWidget3::sendData);
    connect(gs, &GetSerial::receivedSPO2data, &spo2Plot, &PlotWidget2::sendData);

    connect(gs, &GetSerial::receivedHRdata, &hr, &HRWidget::setData);

    connect(gs, &GetSerial::receivedST1data, &st, &STWidget::setST1Num);
    connect(gs, &GetSerial::receivedST2data, &st, &STWidget::setST2Num);
    connect(gs, &GetSerial::receivedPVCdata, &st, &STWidget::setPVCNum);

    connect(gs, &GetSerial::receivedLBPdata, &nibp, &NIBPWidget::setLowPa);
    connect(gs, &GetSerial::receivedHBPdata, &nibp, &NIBPWidget::setHighPa);
    connect(gs, &GetSerial::receivedIBPdata, &nibp, &NIBPWidget::setAverage);

    //connect(gs, &GetSerial::receivedSPO2Wdata, &spo2, &SPO2Widget::setDataNum);
    //connect(gs, &GetSerial::receivedBPMdata, &spo2, &SPO2Widget::setBPMNum);
    connect(com, &QWidgetEcgCom::sendbpm, &spo2, &SPO2Widget::setBPMNum);
    connect(com, &QWidgetEcgCom::sendbpm, &spo2, &SPO2Widget::setDataNum);

    connect(gs, &GetSerial::receivedT1data, &temp, &TEMPWidget::setT1Data);
    connect(gs, &GetSerial::receivedT2data, &temp, &TEMPWidget::setT2Data);
    connect(gs, &GetSerial::receivedTDdata, &temp, &TEMPWidget::setTDData);

    connect(gs, &GetSerial::receivedRESPdata, &resp, &RESPWidget::setData);

    connect(gs, &GetSerial::receivedCO2data, &co2, &CO2Widget::setCO2Num);
    connect(gs, &GetSerial::receivedAWRRdata, &co2, &CO2Widget::setAWRRNum);
    connect(gs, &GetSerial::receivedINSdata, &co2, &CO2Widget::setINSNum);

    //gs->connectPort();

    cl.moveToThread(&tcpThread);
    tcpThread.start();
    cl.hr = &hr;
    cl.st = &st;
    cl.nibp = &nibp;
    cl.spo2 = &spo2;
    cl.temp = &temp;
    cl.resp = &resp;
    cl.co2 = &co2;

    connect(&title, &TitleBar::middleTCP, &cl, &Client::setTCPIP);
    connect(this, &MainWidget::initTCPSig, &cl, &Client::initALL);
    connect(&cl, &Client::facilityIDchanged, title.pinfo, &PatientInfoWidget::getfacilityID);

    qRegisterMetaType<QList<int>>("QList<int>");
    qRegisterMetaType<QList<int>>("QList<int>&");
    connect(&ecgiiPlot, &PlotWidget::dataFulledForTCP, &cl, &Client::sendTCPWaves);
    connect(&spo2Plot, &PlotWidget2::dataFulledForTCP, &cl, &Client::sendTCPWaves);
    connect(&bpPlot, &PlotWidget3::dataFulledForTCP, &cl, &Client::sendTCPWaves);

    connect(&cl, &Client::ecgDataSended, &ecgiiPlot, &PlotWidget::dataSendedTCP);
    connect(&cl, &Client::spo2DataSended, &spo2Plot, &PlotWidget2::dataSendedTCP);
    connect(&cl, &Client::bpDataSended, &bpPlot, &PlotWidget3::dataSendedTCP);

    connect(&cl, &Client::connectedChangedSig, &ecgiiPlot, &PlotWidget::connectedChanged);
    connect(&cl, &Client::connectedChangedSig, &spo2Plot, &PlotWidget2::connectedChanged);
    connect(&cl, &Client::connectedChangedSig, &bpPlot, &PlotWidget3::connectedChanged);
    emit initTCPSig();

    title.ds->gs = gs;
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

void MainWidget::setFull()
{
    this->showFullScreen();
}

void MainWidget::setNotFull()
{
    this->showNormal();
}
