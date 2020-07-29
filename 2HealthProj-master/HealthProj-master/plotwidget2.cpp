#include "plotwidget2.h"
#include <QDebug>

int ecgWave2[] =
{
    0x21, 0x21, 0x22, 0x22, 0x23, 0x22, 0x22, 0x21, 0x21,
    0x20, 0x20, 0x1f, 0x1e, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
    0x19, 0x18, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12,
    0x11, 0x11, 0x10, 0x10, 0x0f, 0x0f, 0x0e, 0x0d, 0x0c,
    0x0c, 0x0b, 0x0a, 0x09, 0x09, 0x08, 0x07, 0x06, 0x06,
    0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x03, 0x06, 0x0a, 0x0e, 0x13, 0x18, 0x1d,
    0x23, 0x28, 0x2d, 0x32, 0x37, 0x3b, 0x40, 0x44, 0x49,
    0x4d, 0x51, 0x54, 0x57, 0x58, 0x5a, 0x5a, 0x5a, 0x59,
    0x59, 0x57, 0x55, 0x52, 0x50, 0x4c, 0x49, 0x45, 0x42,
    0x3e, 0x3b, 0x37, 0x34, 0x31, 0x2f, 0x2c, 0x29, 0x26,
    0x24, 0x22, 0x20, 0x1f, 0x1f, 0x1e, 0x1e, 0x1d, 0x1d,
    0x1e, 0x1f, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x22,
    0x22, 0x21, 0x21, 0x20, 0x20, 0x1f, 0x1e, 0x1d, 0x1c,
    0x1b, 0x1b, 0x1a, 0x19, 0x18, 0x18, 0x17, 0x16, 0x15,
    0x14, 0x13, 0x12, 0x11, 0x11, 0x10, 0x10, 0x0f, 0x0f,
    0x0e, 0x0d, 0x0c, 0x0c, 0x0b, 0x0a, 0x09, 0x09, 0x08,
    0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03,
    0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0a, 0x0e,
    0x13, 0x18, 0x1d, 0x23, 0x28, 0x2d, 0x32, 0x37, 0x3b,
    0x40, 0x44, 0x49, 0x4d, 0x51, 0x54, 0x57, 0x58, 0x5a,
    0x5a, 0x5a, 0x59, 0x59, 0x57, 0x55, 0x52, 0x50, 0x4c,
    0x49, 0x45, 0x42, 0x3e, 0x3b, 0x37, 0x34, 0x31, 0x2f,
    0x2c, 0x29, 0x26, 0x24, 0x22, 0x20, 0x1f, 0x1f, 0x1e,
    0x1e, 0x1d, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x21, 0x22,
    0x22, 0x23, 0x22, 0x22, 0x21,
};



PlotWidget2::PlotWidget2(QWidget *parent,
                       QColor color_, int xScale_, double y0_, double yScale_, int updateInterval_) : QWidget(parent),
                        color(color_), xScale(xScale_), y0(y0_), yScale(yScale_), updateInterval(updateInterval_)
{
    connect(&timer, &QTimer::timeout, this, &PlotWidget2::paintSlot);
    timer.setInterval(updateInterval);
    painter = new QPainter;
    pix = new QPixmap(this->width(), this->height());
    pix->fill(Qt::black);
    label.setParent(this);
    label.move(0,0);
    label.setStyleSheet("font: 10pt \"黑体\"; background-color: black; color: white");
}

PlotWidget2::~PlotWidget2()
{
    timer.stop();
    delete painter;
}

void PlotWidget2::sendData(double d)
{
    data.append(pix->height() - (d-y0)*pix->height()/(yScale-y0));
    time.append(t*pix->width()/xScale);
    if(!timer.isActive())
        timer.start(updateInterval);
}

void PlotWidget2::paintEvent(QPaintEvent *event)
{
    label.setText(text);
    label.adjustSize();
    Q_UNUSED(event);
    paintData();
    painter->begin(this);
    painter->drawPixmap(0, 0, this->width(), this->height(),*pix);
    painter->end();
}

void PlotWidget2::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    *pix = pix->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    t = 0;
    data.clear();
    time.clear();
    pix->fill(Qt::black);
}

/*void PlotWidget::paintData()
{
    int s = data.size()-1;
    int dis = 0;
    painter->begin(pix);
    painter->setRenderHint(QPainter::Antialiasing,true);
    if(s>-1)
    {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::black);
        if(s<10)
            painter->drawRect(time.at(s), 0, 10, this->height());
        painter->drawRect(time.at(s)+10, 0, 10, this->height());
    }

    if(s>1)
    {
        dis = 1;
        painter->setPen(QPen(color, 2));
        while(time.at(s-dis) == time.at(s) && dis < 8 && dis < s)
        {
            data[s] = (data.at(s) + data.at(s-dis))/2;
            dis++;
        }
        if(dataForTCP.length() < 200)
            dataForTCP.append((pix->height() - data.at(s-dis))*(yScale-y0)/pix->height() + y0);
        painter->drawLine(time.at(s-dis), data.at(s-dis),time.at(s), data.at(s));
    }
    painter->end();
}*/


void PlotWidget2::paintData()
{
    // 1.将波形画到pixmap上
    // 1.1 定义painter
    painter->begin(pix);
    painter->setRenderHint(QPainter::Antialiasing,true);
    //painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::black);
    painter->setPen(QPen(color, 2));
    // 1.2擦除当前列
    painter->save();
    painter->setPen(Qt::black);
    painter->drawLine(index, 0, index,  pix->height());
    painter->drawLine(index+1, 0, index+1,  pix->height());
    painter->drawLine(index+2, 0, index+2,  pix->height());
    painter->drawLine(index+3, 0, index+3,  pix->height());
    painter->drawLine(index+4, 0, index+4,  pix->height());
    painter->drawLine(index+5, 0, index+5,  pix->height());
    painter->drawLine(index+6, 0, index+6,  pix->height());
    painter->restore();

    // 1.3更新绘图参数，水平方向循环绘图
    index = index + 2;
    if (index > pix->width())
    {
        index = 2;
    }
    QPoint lineStart;
    QPoint lineEnd;
    // 设置起始、结束的x坐标
    lineStart.setX(index-2);
    lineEnd.setX(index);

    // 设置起始点、结束点y坐标
    // 起始点的y值：
    lineStart.setY(round((double)pix->height()/2 - (((double)ecgWave2[ecgDataIndex]- 128)/200 * pix->height()/2)));


    // 更新参数循环取数
    ecgDataIndex += 5;
    if (ecgDataIndex >= sizeof(ecgWave2)/sizeof(int))
    {
        ecgDataIndex = 0;
    }
    // 设置结束点的y值
    lineEnd.setY(round((double)pix->height()/2 - (((double)ecgWave2[ecgDataIndex] - 128)/200 * pix->height()/2)));
    // 1.4 绘制直线
    painter->drawLine(lineStart, lineEnd);

    // 2. 更新
    this->update();

    painter->end();
}


void PlotWidget2::paintSlot()
{
    t += 1;
    TCPInterval += 1;
    if(t==xScale)
    {
        t = 0;
        data.clear();
        time.clear();
    }
    if(TCPInterval >= 2000)
    {
        emittedFlag = false;
        TCPInterval = 0;
    }
    if(dataForTCP.size() == 200 && emittedFlag == false && connected)
    {
        emit dataFulledForTCP(plotflag, dataForTCP);
        emittedFlag = true;
    }
    this->update();
}

void PlotWidget2::dataSendedTCP()
{
    emittedFlag = false;
    dataForTCP.clear();
    TCPInterval = 0;
}

void PlotWidget2::connectedChanged()
{
    connected = true;
}

