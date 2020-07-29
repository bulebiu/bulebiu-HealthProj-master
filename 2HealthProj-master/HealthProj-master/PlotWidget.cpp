#include "PlotWidget.h"
#include <QDebug>

int ecgWave[] = {
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2008, 2016, 2016, 2016, 2024, 2032, 2048,
       2064, 2064, 2064, 2072, 2080, 2080, 2080, 2088, 2096, 2104,
       2112, 2112, 2112, 2112, 2112, 2112, 2104, 2096, 2088,
       2080, 2080, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2032,
       2032, 2016, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 1992, 1984, 1976,
       1968, 1960, 1952, 1944, 1936, 1944, 1952, 2016, 2080, 2136,
       2192, 2256, 2320, 2376, 2432, 2488, 2544, 2568, 2592, 2536,
       2480, 2424, 2368, 2304, 2240, 2184, 2128, 2072, 2016, 1968,
       1920, 1928, 1936, 1944, 1952, 1960, 1968, 1984, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2008, 2016, 2024, 2032, 2032,
       2032, 2048, 2064, 2064, 2064, 2072, 2080, 2088, 2096, 2104,
       2112, 2112, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2160,
       2160, 2160, 2160, 2168, 2176, 2176, 2176, 2184, 2192,
       2192, 2192, 2192, 2200, 2208, 2208, 2208, 2208, 2208, 2208,
       2208, 2200, 2192, 2192, 2192, 2184, 2176, 2176, 2176, 2168,
       2160, 2160, 2160, 2144, 2128, 2128, 2128, 2128, 2128, 2112,
       2096, 2088, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2024,
       2016, 2016, 2016, 2008, 2000, 2000, 2000, 2000, 2000,
       2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};


PlotWidget::PlotWidget(QWidget *parent,
                       QColor color_, int xScale_, double y0_, double yScale_, int updateInterval_) : QWidget(parent),
                        color(color_), xScale(xScale_), y0(y0_), yScale(yScale_), updateInterval(updateInterval_)
{
    connect(&timer, &QTimer::timeout, this, &PlotWidget::paintSlot);
    timer.setInterval(updateInterval);
    painter = new QPainter;
    pix = new QPixmap(this->width(), this->height());
    pix->fill(Qt::black);
    label.setParent(this);
    label.move(0,0);
    label.setStyleSheet("font: 10pt \"黑体\"; background-color: black; color: white");
}

PlotWidget::~PlotWidget()
{
    timer.stop();
    delete painter;
}

void PlotWidget::sendData(double d)
{
    data.append(pix->height() - (d-y0)*pix->height()/(yScale-y0));
    time.append(t*pix->width()/xScale);
    if(!timer.isActive())
        timer.start(updateInterval);
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    label.setText(text);
    label.adjustSize();
    Q_UNUSED(event);
    paintData();
    painter->begin(this);
    painter->drawPixmap(0, 0, this->width(), this->height(),*pix);
    painter->end();
}

void PlotWidget::resizeEvent(QResizeEvent *event)
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


void PlotWidget::paintData()
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
    lineStart.setY(round((double)pix->height()/2 - (((double)ecgWave[ecgDataIndex] - 2048)/600 * pix->height()/2)));

    // 更新参数循环取数
    ecgDataIndex += 5;
    if (ecgDataIndex >= sizeof(ecgWave)/sizeof(int))
    {
        ecgDataIndex = 0;
    }

    // 设置结束点的y值
    lineEnd.setY(round((double)pix->height()/2 - (((double)ecgWave[ecgDataIndex] - 2048)/600 * pix->height()/2)));

    // 1.4 绘制直线
    painter->drawLine(lineStart, lineEnd);

    // 2. 更新
    this->update();

    painter->end();
}


void PlotWidget::paintSlot()
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

void PlotWidget::dataSendedTCP()
{
    emittedFlag = false;
    dataForTCP.clear();
    TCPInterval = 0;
}

void PlotWidget::connectedChanged()
{
    connected = true;
}

