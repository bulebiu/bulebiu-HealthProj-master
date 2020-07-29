#include "tempwidget.h"

TEMPWidget::TEMPWidget(QWidget *parent) : QWidget(parent)
{
    head->setStyleSheet("background-color:rgb(87, 96, 111)");
    head->setFixedHeight(30);
    head->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    title->setStyleSheet("color:white;font: 11pt , SimHei;");

    //头部标签数据
    title->setText("TEMP");
    // 中部标签数据
    t1->setText("T1 -?-");
    t2->setText("T2 -?-");
    td->setText("TD -?-");
    c->setText("℃");
    //头部布局
    layoutHead->addWidget(title,0,Qt::AlignLeft);
    layoutHead->addWidget(tu, 0 ,Qt::AlignRight );
    head->setLayout(layoutHead);
    //中部布局
    layoutBody->addWidget(t1,0, Qt::AlignHCenter|Qt::AlignTop);
    layoutBody->addWidget(t2, 0, Qt::AlignHCenter|Qt::AlignBottom);
    z1->setLayout(layoutBody);
    layoutBody2->addWidget(td, 0, Qt::AlignCenter);
    z2->setLayout(layoutBody2);
    layoutBody1->addWidget(z1);
    layoutBody1->addWidget(z2);
    body->setLayout(layoutBody1);
    layoutBody->setMargin(0);
    layoutBody1->setMargin(0);
    layoutBody2->setMargin(0);
    layoutBody->setSpacing(0);
    layoutBody1->setSpacing(0);
    layoutBody2->setSpacing(0);
    //整体布局
    layout->addWidget(head,0);
    layout->addWidget(c,0,Qt::AlignRight);
    layout->addWidget(body);
    layout->addWidget(nothing);
    layout->setMargin(0);
    this->setLayout(layout);
}

void TEMPWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TEMPWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(head->height()-18, Qt::SmoothTransformation);
    tu->setPixmap(*pix);
    int w = this->width(), h = this->height();
    int px22 = w*21/128 > h*21/128? h*21/128 : w*21/128;
    //int px20 = w*20/128 > h*20/128? h*20/128 : w*20/128;
    t1->setStyleSheet(QString("color: rgb(224, 86, 253);font: %1px , SimHei;").arg(px22));
    t2->setStyleSheet(QString("color: rgb(224, 86, 253);font: %1px , SimHei;").arg(px22));
    td->setStyleSheet(QString("color: rgb(224, 86, 253);font: %1px , SimHei;").arg(px22));
    c->setStyleSheet(QString("color: rgb(224, 86, 253);font: %1px , SimHei;").arg(px22));
}

void TEMPWidget::setT1Data(short int t1Num)
{
    if(t1Num != -1)
        t1->setText(QString("T1 %1").arg(t1Num));
    dataForTCPSend1 = t1Num;
}

void TEMPWidget::setT2Data(short int t2Num)
{
    if(t2Num != -1)
        t2->setText(QString("T2 %1").arg(t2Num));
    dataForTCPSend2 = t2Num;
}

void TEMPWidget::setTDData(short int tdNum)
{
    if(tdNum != -1)
        td->setText(QString("TD %1").arg(tdNum));
    dataForTCPSend3 = tdNum;
}

