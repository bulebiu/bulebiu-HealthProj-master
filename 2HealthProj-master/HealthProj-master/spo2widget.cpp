#include "spo2widget.h"

SPO2Widget::SPO2Widget(QWidget *parent) : QWidget(parent)
{
    head->setFixedHeight(30);
    head->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    title->setStyleSheet("color:white;font: 11pt ,SimHei;");

     //头部标签数据
    title->setText("SPO2");
    //tu->setPixmap();
    //中部标签数据
    data->setText("98");
    fu->setText("%");
    //底部标签数据
    bpm->setText("84 bpm");
    //头部布局
    layoutHead->addWidget(title,0,Qt::AlignLeft);
    layoutHead->addWidget(tu,0,Qt::AlignRight );
    head->setStyleSheet("background-color:rgb(87, 96, 111)");
    head->setLayout(layoutHead);
    //中部布局
    layoutBody->addWidget(nothing);
    layoutBody->addWidget(data,0,Qt::AlignCenter);
    layoutBody->addWidget(fu,0,Qt::AlignRight | Qt::AlignTop);
    layoutBody->setMargin(2);
    body->setLayout(layoutBody);
    body->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    //底部布局
    layoutBottom->addWidget(bpm,0,Qt::AlignRight);
    layoutBottom->addSpacing(6);
    layoutBottom->setMargin(0);
    bottom->setLayout(layoutBottom);
    bottom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    //整体布局
    layout->addWidget(head,0);
    layout->addWidget(body, 1);
    layout->addWidget(bottom, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void SPO2Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SPO2Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(head->height() - 18, Qt::SmoothTransformation);
    tu->setPixmap(*pix);
    int w = this->width(), h = this->height();
    int px15 = w*15/128 > h*15/128? h*15/128 : w*15/128;
    int px50 = w*45/128 > h*45/128? h*45/128 : w*45/128;

    data->setStyleSheet(QString("color: rgb(255, 107, 129);font: %1px, SimHei;").arg(px50));
    fu->setStyleSheet(QString("color:rgb(255, 107, 129);font: %1px ,SimHei;").arg(px15));
    nothing->setStyleSheet(QString("color:rgb(255, 107, 129);font: %1px ,SimHei;").arg(px15));
    bpm->setStyleSheet(QString("color:rgb(255, 107, 129);font: %1px ,SimHei;").arg(px15));
}

void SPO2Widget::setBPMNum(short int bpmNum)
{
    if(bpmNum != -1)
        bpm->setText(QString("%1 bpm").arg(bpmNum));
    dataForTCPSend1 = bpmNum;
}

void SPO2Widget::setDataNum(short int dataNum)
{
    if(dataNum != -1)
        data->setText(QString("%1").arg(dataNum));
    dataForTCPSend2 = dataNum;
}
