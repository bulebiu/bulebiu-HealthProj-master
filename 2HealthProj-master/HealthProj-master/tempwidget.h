#ifndef TEMPWIDGET_H
#define TEMPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLayout>
#include <QLabel>
#include <QPixmap>
#include "labelbutton.h"

class TEMPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TEMPWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    int dataForTCPSend1;
    int dataForTCPSend2;
    int dataForTCPSend3;
private:

    QVBoxLayout *layout=new QVBoxLayout;
    QVBoxLayout *layoutBody=new QVBoxLayout;
    QHBoxLayout *layoutHead=new QHBoxLayout;
    QHBoxLayout *layoutBody2=new QHBoxLayout;
    QHBoxLayout *layoutBody1=new QHBoxLayout;

    QWidget *head=new QWidget;
    QWidget *body=new QWidget;
    QWidget *z1=new QWidget;
    QWidget *z2=new QWidget;
    QLabel *t1=new QLabel;
    QLabel *t2=new QLabel;
    QLabel *td=new QLabel;
    QLabel *c=new QLabel;
    QLabel *nothing=new QLabel;
    QLabel *title=new QLabel;
    LabelButton *tu=new LabelButton;
    QPixmap *pix = new QPixmap(":/icons/settings.png");

public slots:
    void setT1Data(short int t1Num);
    void setT2Data(short int t2Num);
    void setTDData(short int tdNum);

signals:

};

#endif // TEMPWIDGET_H
