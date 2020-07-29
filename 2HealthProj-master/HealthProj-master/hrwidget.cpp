#include "hrwidget.h"
HRWidget::HRWidget(QWidget *parent) : QWidget(parent)
{
    title->setText("HR");
    data->setText("80");
    bpm->setText("bpm");
    title->setStyleSheet("color:white; font: 11pt, SimHei");
    titlebar->setStyleSheet("background-color:rgb(87, 96, 111);");

    titlebar->setFixedHeight(30);
    titlebarLayout->addWidget(title, 0, Qt::AlignLeft);
    titlebarLayout->addWidget(pixContainer, 0, Qt::AlignRight);
    titlebar->setLayout(titlebarLayout);

    hrlayout->addWidget(titlebar);
    hrlayout->addWidget(bpm,0,Qt::AlignRight|Qt::AlignTop);
    hrlayout->addWidget(data,1,Qt::AlignCenter);
    hrlayout->addWidget(bpm2nothing,0,Qt::AlignRight|Qt::AlignTop);
    hrlayout->setMargin(0);
    hrlayout->setSpacing(0);
    this->setLayout(hrlayout);
}

void HRWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void HRWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(titlebar->height()-18);
    pixContainer->setPixmap(*pix);
    int w = this->width(), h = this->height();
    int px15 = w*15/128 > h*15/128? h*15/128 : w*15/128;
    int px50 = w*50/128 > h*50/128? h*50/128 : w*50/128;
    data->setStyleSheet(QString("color:rgb(123, 237, 159); font: %1px, SimHei").arg(px50));
    bpm->setStyleSheet(QString("color:rgb(123, 237, 159); font: %1px, SimHei").arg(px15));
    bpm2nothing->setStyleSheet(QString("color:rgb(123, 237, 159); font: %1px, SimHei").arg(px15));
}

void HRWidget::setData(short int bpmNum)
{
    if(bpmNum != -1)
        data->setText(QString("%1").arg(bpmNum));
    dataForTCPSend = bpmNum;
}
