#include "stwidget.h"
#include"hrwidget.h"
STWidget::STWidget(QWidget *parent) : QWidget(parent)
{
    //ST\PVC内容及样式
    title->setText("ST");
    stl1->setText("ST1 -?-");
    stl2->setText("ST2 -?-");
    pvcs->setText("PVCs -?-");
    title->setStyleSheet("color:white;font: 11pt, SimHei;");
    titleBar->setStyleSheet("background-color:rgb(87, 96, 111);");
    pixContainer->setPixmap(*pix);

    //布局
    stlayout->addWidget(titleBar,0);
    stlayout->addWidget(stl1,1, Qt::AlignHCenter);
    stlayout->addWidget(stl2,1, Qt::AlignHCenter);
    stlayout->addWidget(pvcs,1, Qt::AlignHCenter);
    titleBarLayout->addWidget(title, 0, Qt::AlignLeft);
    titleBarLayout->addWidget(pixContainer, 0, Qt::AlignRight);
    titleBar->setLayout(titleBarLayout);
    titleBar->setFixedHeight(30);
    stlayout->setMargin(0);
    stlayout->setSpacing(0);

    this->setLayout(stlayout);
}

void STWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void STWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaledToHeight(titleBar->height()-18, Qt::SmoothTransformation);
    pixContainer->setPixmap(*pix);
    int w = this->width();
    int h = this->height();
    int px20 = w*20/128 > h*20/128? h*20/128 : w*20/128;
    stl1->setStyleSheet(QString("color:rgb(123, 237, 159);font: %1px, SimHei;").arg(px20));
    stl2->setStyleSheet(QString("color:rgb(123, 237, 159);font: %1px, SimHei;").arg(px20));
    pvcs->setStyleSheet(QString("color:rgb(123, 237, 159);font: %1px, SimHei;").arg(px20));
}

void STWidget::setST1Num(short int st1Num)
{
    if(st1Num != -1)
        stl1->setText(QString("ST1 %1").arg(st1Num));
    dataForTCPSend1 = st1Num;
}

void STWidget::setST2Num(short int st2Num)
{
    if(st2Num != -1)
        stl2->setText(QString("ST2 %1").arg(st2Num));
    dataForTCPSend2 = st2Num;
}

void STWidget::setPVCNum(short int pvcsNum)
{
    if(pvcsNum != -1)
        pvcs->setText(QString("PVCs %1").arg(pvcsNum));
    dataForTCPSend3 = pvcsNum;
}
