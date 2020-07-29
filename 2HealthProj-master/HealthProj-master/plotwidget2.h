#ifndef PLOTWIDGET2_H
#define PLOTWIDGET2_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

class PlotWidget2 : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget2(QWidget *parent = nullptr, QColor color_ = Qt::white, int xScale_ = 500, double y0_ = -20, double yScale_ = 20, int updateInterval_ = 5);
    ~PlotWidget2();
    QColor color = Qt::white; //笔刷颜色
    int xScale = 500; //x范围
    double y0 = -20; //y起始值
    double yScale = 20; //y最大值
    int plotflag = -1;
    int updateInterval = 10; //采样间隔ms数，需符合奈奎斯特准则
    int TCPInterval = 0;
    QString text = "";

    void paintEvent(QPaintEvent *event) override; //重写重绘函数
    void resizeEvent(QResizeEvent *event) override;

    QList<int> dataForTCP;

private:
    QList<int> data; //数据
    QList<int> time; //数据对应时间
    QLabel label;
    QPainter *painter; //主painter
    QTimer timer; //重绘定时器
    QPixmap *pix;
    bool emittedFlag = false;
    bool connected = false;

    int t = 0; //当前时间
    int index = 0;          // x
    int ecgDataIndex = 0;   // y：取数组数据的索引
    void paintData(); //绘制数据

public slots:
    void sendData(double d); //外部获取数据函数
    void paintSlot(); //定时绘制
    void dataSendedTCP();
    void connectedChanged();

signals:
    void dataFulledForTCP(int flag, QList<int>& dataF);
};

#endif
