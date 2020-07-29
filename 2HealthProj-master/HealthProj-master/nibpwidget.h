#ifndef NIBPWIDGET_H
#define NIBPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include "labelbutton.h"
class NIBPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NIBPWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QVBoxLayout *playoutWhole = new QVBoxLayout;
    QVBoxLayout *playoutLeft = new QVBoxLayout;
    QVBoxLayout *playoutRight = new QVBoxLayout;
    QVBoxLayout *playoutmiddle =new QVBoxLayout;
    QHBoxLayout *playoutBody = new QHBoxLayout;
    QHBoxLayout *playoutHead = new QHBoxLayout;

    QWidget *wholehead = new QWidget;
    QWidget *wholebody = new QWidget;
    QWidget *bodymiddle = new QWidget;
    QWidget *bodyright = new QWidget;
    QWidget *bodyLeft = new QWidget;

    QLabel *title = new QLabel;
    LabelButton *setting = new LabelButton;
    QLabel *righttop = new QLabel;
    QLabel *rightmiddle = new QLabel;
    QLabel *rightbottom = new QLabel;
    QLabel *middlemiddle = new QLabel;
    QLabel *bodyleftLabel = new QLabel;
    QLabel *bodyleftUp = new QLabel;

    QTimer timer;
    QString timeStr;
    QPixmap *pix = new QPixmap(":/icons/settings.png");

    int dataForTCPSend1;
    int dataForTCPSend2;
    int dataForTCPSend3;

public slots:
    void setLCDTime();
    void setLowPa(short int lowPa);
    void setHighPa(short int highPa);
    void setAverage(short int average);

private:
    QLabel *pCurrentTimeLabel = new QLabel(this);
    QTime time;

signals:

};

#endif // NIBPWIDGET_H
