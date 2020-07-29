#include "co2widget.h"

CO2Widget::CO2Widget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background:rgb(0,0,0)");
    head->setFixedHeight(30);
    head->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    body->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    bottom->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    title->setStyleSheet("color:rgb(255, 255, 255);font: 11pt , SimHei;");


    //头部标签数据写入
    title->setText("CO2");
    setting->setPixmap(*pix);

    //中部标签数据写入
    data->setText("-?-");
    bpm->setText("mmHg");

    //尾部标签写入
    ins->setText("ins -?-");
    awrr->setText("awrr -?-");

    //头部布局
    layoutHead->addWidget(title,0,Qt::AlignLeft);
    layoutHead->addWidget(setting, 0 ,Qt::AlignRight );
    head->setStyleSheet("background-color:rgb(87, 96, 111)");
    head->setLayout(layoutHead);
    //中部布局
    layoutBody->addWidget(data, 0, Qt::AlignCenter|Qt::AlignBottom);
    layoutBody->addWidget(bpm ,0 ,Qt::AlignRight | Qt::AlignTop);
    body->setLayout(layoutBody);
    //尾部布局
    layoutBottom->addWidget(ins, 0, Qt::AlignCenter|Qt::AlignTop);
    layoutBottom->addWidget(awrr, 0, Qt::AlignCenter|Qt::AlignTop);
    bottom->setLayout(layoutBottom);

    //整体布局
    layoutResp->addWidget(head,0, Qt::AlignTop);
    layoutResp->addWidget(body, 0,Qt::AlignTop);
    layoutResp->addWidget(bottom, 0, Qt::AlignTop);
    layoutResp->setMargin(0);
    layoutResp->setSpacing(0);
    this->setLayout(layoutResp);
}

void CO2Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    int h = this->height();
    int px15 = h*15/128;
    //int px25 = h*25/128;
    int px40 = h*40/128;
    data->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px40));
    bpm->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px15));
    ins->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px15));
    awrr->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px15));
}

void CO2Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(head->height()-18, Qt::SmoothTransformation);
    setting->setPixmap(*pix);
}

void CO2Widget::setINSNum(short int insNum)
{
    if(insNum != -1)
        data->setText(QString("%1").arg(insNum));
    dataForTCPSend3 = insNum;

}

void CO2Widget::setAWRRNum(short int awrrNum)
{
    if(awrrNum != -1)
        data->setText(QString("%1").arg(awrrNum));
    dataForTCPSend2 = awrrNum;
}

void CO2Widget::setCO2Num(short int co2num)
{
    if(co2num != -1)
        data->setText(QString("%1").arg(co2num));
    dataForTCPSend1 = co2num;
}
