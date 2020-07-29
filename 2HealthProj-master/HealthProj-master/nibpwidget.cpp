#include "nibpwidget.h"

NIBPWidget::NIBPWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background:rgb(0,0,0)");

    playoutHead->addWidget(title,0,Qt::AlignLeft);
    playoutHead->addWidget(setting,0,Qt::AlignRight);
    wholehead->setFixedHeight(30);
    wholehead->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    wholehead->setLayout(playoutHead);
    playoutBody->addWidget(bodyLeft,1);
    playoutBody->addWidget(bodymiddle,1);
    playoutBody->addWidget(bodyright,1);
    playoutLeft->addWidget(bodyleftUp, 0);
    playoutLeft->addWidget(bodyleftLabel, 1, Qt::AlignCenter);
    bodyLeft->setLayout(playoutLeft);
    playoutmiddle->addWidget(pCurrentTimeLabel,0, Qt::AlignHCenter|Qt::AlignTop);
    playoutmiddle->addWidget(middlemiddle,1, Qt::AlignCenter);
    bodymiddle->setLayout(playoutmiddle);
    playoutRight->addWidget(righttop,0, Qt::AlignRight|Qt::AlignTop);
    playoutRight->addWidget(rightmiddle,1, Qt::AlignCenter);
    bodyright->setLayout(playoutRight);
    wholebody->setLayout(playoutBody);
    playoutWhole->addWidget(wholehead,0);
    playoutWhole->addWidget(wholebody,1);
    playoutWhole->setMargin(0);
    playoutLeft->setMargin(0);
    playoutRight->setMargin(0);
    playoutmiddle->setMargin(0);
    playoutBody->setMargin(0);
    this->setLayout(playoutWhole);

    title->setStyleSheet("color:rgb(255, 255, 255); font: 15px , SimHei;");
    wholehead->setStyleSheet("background-color:rgb(87, 96, 111)");

    time = QTime::currentTime();
    timer.start(50);
    pCurrentTimeLabel->setText(time.toString("hh:mm:ss"));
    setting->setPixmap(*pix);
    title->setText("NIBP");
    bodyleftLabel->setText("-?-");
    middlemiddle->setText("/ -?-");
    righttop->setText("mmHg");
    rightmiddle->setText("-?-");
    connect(&timer, &QTimer::timeout, this, &NIBPWidget::setLCDTime);
}

void NIBPWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(wholehead->height() - 18, Qt::SmoothTransformation);
    setting->setPixmap(*pix);
    int w = this->width();
    int h = this->height();
    int px12 = w*12/256 > h*12/128? h*12/128 : w*12/256;
    int px25 = w*25/256 > h*25/128? h*25/128 : w*25/256;
    int px40 = w*40/256 > h*40/128? h*40/128 : w*40/256;

    pCurrentTimeLabel->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px12));
    bodyleftUp->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px12));
    bodyleftLabel->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px25));
    middlemiddle->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px40));
    righttop->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px12));
    rightmiddle->setStyleSheet(QString("color: rgb(112, 161, 255);font: %1px, SimHei;").arg(px40));
}

void NIBPWidget::setLCDTime()
{
    time = QTime::currentTime();
    timeStr = time.toString("hh:mm:ss");
    pCurrentTimeLabel->setText(timeStr);
}

void NIBPWidget::setLowPa(short int lowPa)
{
    if(lowPa != -1)
        middlemiddle->setText(QString("%1").arg(lowPa));
    dataForTCPSend2 = lowPa;
}

void NIBPWidget::setHighPa(short int highPa)
{
    if(highPa != -1)
        bodyleftLabel->setText(QString("%1").arg(highPa));
    dataForTCPSend1 = highPa;
}

void NIBPWidget::setAverage(short int average)
{
    if(average != -1)
        rightmiddle->setText(QString("%1").arg(average));
    dataForTCPSend3 = average;
}


void NIBPWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

