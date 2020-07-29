#include "plotwidget3.h"
#include <QDebug>

int ecgWave3[] =
{
  0x0f, 0x10, 0x10, 0x11, 0x12, 0x12, 0x12, 0x13, 0x13,
  0x14, 0x14, 0x14, 0x14, 0x15, 0x17, 0x17, 0x17, 0x18,
  0x18, 0x19, 0x19, 0x19, 0x19, 0x1a, 0x19, 0x1a, 0x1a,
  0x1b, 0x1b, 0x1b, 0x1c, 0x1c, 0x1b, 0x1b, 0x1a, 0x1a,
  0x1a, 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17, 0x15,
  0x15, 0x15, 0x14, 0x15, 0x14, 0x14, 0x14, 0x15, 0x15,
  0x14, 0x14, 0x15, 0x14, 0x14, 0x14, 0x15, 0x17, 0x17,
  0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x19, 0x1a, 0x1b,
  0x1c, 0x1d, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x24,
  0x24, 0x26, 0x26, 0x26, 0x26, 0x24, 0x23, 0x23, 0x23,
  0x23, 0x22, 0x21, 0x20, 0x1d, 0x1d, 0x1c, 0x1c, 0x1c,
  0x1c, 0x1c, 0x1c, 0x1c, 0x1b, 0x1c, 0x1b, 0x1a, 0x1a,
  0x19, 0x18, 0x17, 0x15, 0x14, 0x12, 0x12, 0x11, 0x10,
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f
};


PlotWidget3::PlotWidget3(QWidget *parent,
                       QColor color_, int xScale_, double y0_, double yScale_, int updateInterval_) : QWidget(parent),
                        color(color_), xScale(xScale_), y0(y0_), yScale(yScale_), updateInterval(updateInterval_)
{
    connect(&timer, &QTimer::timeout, this, &PlotWidget3::paintSlot);
    timer.setInterval(updateInterval);
    painter = new QPainter;
    pix = new QPixmap(this->width(), this->height());
    pix->fill(Qt::black);
    label.setParent(this);
    label.move(0,0);
    label.setStyleSheet("font: 10pt \"黑体\"; background-color: black; color: white");
}

PlotWidget3::~PlotWidget3()
{
    timer.stop();
    delete painter;
}

void PlotWidget3::sendData(double d)
{
    data.append(pix->height() - (d-y0)*pix->height()/(yScale-y0));
    time.append(t*pix->width()/xScale);
    if(!timer.isActive())
        timer.start(updateInterval);
}

void PlotWidget3::paintEvent(QPaintEvent *event)
{
    label.setText(text);
    label.adjustSize();
    Q_UNUSED(event);
    paintData();
    painter->begin(this);
    painter->drawPixmap(0, 0, this->width(), this->height(),*pix);
    painter->end();
}

void PlotWidget3::resizeEvent(QResizeEvent *event)
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


void PlotWidget3::paintData()
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
    //qDebug()<<ecgWave3[ecgDataIndex]<<"新数据";
    lineStart.setY(round((double)pix->height()/2 - (((double)ecgWave3[ecgDataIndex]-10)/100 * pix->height())));

    // 更新参数循环取数
    ecgDataIndex += 5;
    if (ecgDataIndex >= sizeof(ecgWave3)/sizeof(int))
    {
        ecgDataIndex = 0;
    }

    // 设置结束点的y值
    lineEnd.setY(round((double)pix->height()/2 - (((double)ecgWave3[ecgDataIndex]-10)/100 * pix->height())));

    // 1.4 绘制直线
    painter->drawLine(lineStart, lineEnd);

    // 2. 更新
    this->update();

    painter->end();
}


void PlotWidget3::paintSlot()
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

void PlotWidget3::dataSendedTCP()
{
    emittedFlag = false;
    dataForTCP.clear();
    TCPInterval = 0;
}

void PlotWidget3::connectedChanged()
{
    connected = true;
}

