#include "respwidget.h"

RESPWidget::RESPWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background:rgb(0,0,0)");
    head->setStyleSheet("background-color:rgb(87, 96, 111)");
    head->setFixedHeight(30);
    head->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    title->setStyleSheet("color:white;font: 11pt , SimHei;");

    //头部标签数据写入
    title->setText("RESP");
    setting->setPixmap(*pix);

    data->setText("-?-");
    bpm->setText("bpm");

    //尾部标签写入
    //ins->setText("ins -?-");
    //awrr->setText("awrr -?-");

    //头部布局
    layoutHead->addWidget(title,0,Qt::AlignLeft);
    layoutHead->addWidget(setting, 0 ,Qt::AlignRight );
    head->setLayout(layoutHead);
    //中部布局
    layoutBody1->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum));
    layoutBody1->addWidget(bpm ,0 ,Qt::AlignRight | Qt::AlignTop);
    layoutBody2->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum));
    layoutBody2->addWidget(data, 1, Qt::AlignCenter|Qt::AlignTop);
    layoutBody2->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum));
    layoutBody->addLayout(layoutBody1, 0);
    layoutBody->addLayout(layoutBody2, 1);
    body->setLayout(layoutBody);
    //尾部布局
    //layoutBottom->addWidget(nothing2);

    //整体布局
    layoutResp->addWidget(head, 0, Qt::AlignTop);
    layoutResp->addWidget(body, 1, Qt::AlignVCenter);
    layoutResp->setSpacing(0);
    layoutResp->setMargin(0);

    this->setLayout(layoutResp);
}

void RESPWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    int w = this->width();
    int h = this->height();
    int px15 = h*15/128 > w*15/128? w*15/128:h*15/128;
    int px40 = h*40/128 > w*40/128? w*40/128:h*40/128;
    data->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px40));
    bpm->setStyleSheet(QString("color:rgb(236, 204, 104);font: %1px , SimHei;").arg(px15));

}

void RESPWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(head->height() - 18, Qt::SmoothTransformation);
    setting->setPixmap(*pix);
}

void RESPWidget::setData(short int bpmData)
{
    if(bpmData != -1)
        data->setText(QString("%1").arg(bpmData));
    dataForTCPSend = bpmData;
}
