#ifndef RESPWIDGET_H
#define RESPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLayout>
#include "labelbutton.h"

class RESPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RESPWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QVBoxLayout *layoutResp = new QVBoxLayout;
    QHBoxLayout *layoutHead = new QHBoxLayout;
    QVBoxLayout *layoutBody = new QVBoxLayout;
    QHBoxLayout *layoutBody1 = new QHBoxLayout;
    QHBoxLayout *layoutBody2 = new QHBoxLayout;
    QWidget *head = new QWidget;
    QWidget *body = new QWidget;

    //头部标签
    QLabel *title = new QLabel;
    LabelButton *setting = new LabelButton;

    //中部标签
    QLabel *nothing1 = new QLabel;
    QLabel *data = new QLabel;
    QLabel *bpm = new QLabel;

    //头部标签图
    QPixmap *pix = new QPixmap(":/icons/settings.png");
    int dataForTCPSend;

public slots:
    void setData(short int bpmData);

signals:

};

#endif // RESPWIDGET_H
