#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    layout->addWidget(peopleIcon);
    layout->addWidget(deviceAndNote);

    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    layout->addWidget(cloudIcon);
    layout->addSpacing(6);
    layout->addWidget(exclamationIcon);
    layout->addSpacing(10);
    layout->addWidget(peopleInfoIcon);
    layout->addSpacing(10);
    layout->addWidget(scaleIcon);
    layout->addSpacing(6);
    layout->setSpacing(8);
    layout->setMargin(6);

    deviceAndNote->setText("设备: " + QNetworkInterface::allInterfaces()[0].hardwareAddress().split(":").join("0") + "  备注: 001");
    deviceAndNote->setStyleSheet("color: white;font: 11pt \"Microsoft Yahei UI Bold\";");

    this->setLayout(layout);
    connect(cloudIcon, &LabelButton::clicked, this, &TitleBar::openTCPWindow);
    connect(exclamationIcon, &LabelButton::clicked, this, &TitleBar::openDSWindow);
    connect(peopleInfoIcon, &LabelButton::clicked, this, &TitleBar::openINFOWindow);
    connect(scaleIcon, &LabelButton::clicked, this, &TitleBar::setFullscreen);
    connect(tcpsettings, &TCPSettingsWidget::tcpipChanged, this, &TitleBar::middleTCPSlot);
    connect(ds, &DeviceSettingsWidget::noteChangeSig, this, &TitleBar::setNotes);
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *peoplePNG = peoplePNG->scaledToHeight(this->height() - 20, Qt::SmoothTransformation);
    *exclamationPNG = exclamationPNG->scaledToHeight(this->height() - 24, Qt::SmoothTransformation);
    *scalePNG = scalePNG->scaledToHeight(this->height() - 24, Qt::SmoothTransformation);
    *cloudPNG = cloudPNG->scaledToHeight(this->height() - 12, Qt::SmoothTransformation);
    *infoPNG = infoPNG->scaledToHeight(this->height() - 24, Qt::SmoothTransformation);
    peopleIcon->setPixmap(*peoplePNG);
    cloudIcon->setPixmap(*cloudPNG);
    peopleInfoIcon->setPixmap(*infoPNG);
    scaleIcon->setPixmap(*scalePNG);
    exclamationIcon->setPixmap(*exclamationPNG);
    tcpsettings->setWindowSize(this->width()/3, this->height()*3);
}

void TitleBar::openDSWindow()
{
    ds->show();
}

void TitleBar::openTCPWindow()
{
    tcpsettings->show();
}

void TitleBar::openINFOWindow()
{
    pinfo->show();
}

void TitleBar::setFullscreen()
{
    if(isfullscreen)
        emit disablefullscreen();
    else
        emit enablefullscreen();
    isfullscreen = !isfullscreen;
}

void TitleBar::middleTCPSlot(QString ip, quint16 port)
{
    emit middleTCP(ip, port);
    pinfo->client.ipAddr = ip;
    pinfo->client.port = port;
}

void TitleBar::setNotes(QString note)
{
    deviceAndNote->setText("设备: " + QNetworkInterface::allInterfaces()[0].hardwareAddress().split(":").join("0") + "  备注: " + note);
}

