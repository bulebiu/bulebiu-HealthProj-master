#ifndef CO2WIDGET_H
#define CO2WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLayout>
#include "labelbutton.h"


class CO2Widget : public QWidget
{
    Q_OBJECT
public:
    explicit CO2Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QVBoxLayout *layoutResp = new QVBoxLayout;
    QHBoxLayout *layoutHead = new QHBoxLayout;
    QHBoxLayout *layoutBody = new QHBoxLayout;
    QHBoxLayout *layoutBottom = new QHBoxLayout;

    QWidget *head = new QWidget;
    QWidget *body = new QWidget;
    QWidget *bottom = new QWidget;

    QLabel *title = new QLabel;
    LabelButton *setting = new LabelButton;

    QLabel *data = new QLabel;
    QLabel *bpm = new QLabel;

    QLabel *ins = new QLabel;
    QLabel *awrr = new QLabel;
    QPixmap *pix = new QPixmap(":/icons/settings.png");
    int dataForTCPSend1;
    int dataForTCPSend2;
    int dataForTCPSend3;

public slots:
    void setCO2Num(short int co2num);
    void setINSNum(short int insnum);
    void setAWRRNum(short int awrrnum);

signals:
};

#endif // CO2WIDGET_H
