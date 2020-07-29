#ifndef SPO2WIDGET_H
#define SPO2WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLayout>
#include <QLabel>
#include "labelbutton.h"

class SPO2Widget : public QWidget
{
    Q_OBJECT
public:
    explicit SPO2Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    int dataForTCPSend1;
    int dataForTCPSend2;

private:
    QVBoxLayout *layout=new QVBoxLayout;
    QHBoxLayout *layoutHead=new QHBoxLayout;
    QHBoxLayout *layoutBody=new QHBoxLayout;
    QHBoxLayout *layoutBottom=new QHBoxLayout;
    QWidget *head=new QWidget;
    QWidget *body=new QWidget;
    QWidget *bottom=new QWidget;
    QLabel *title=new QLabel;
    LabelButton *tu=new LabelButton;
    QLabel *nothing=new QLabel;
    QLabel *data=new QLabel;
    QLabel *fu=new QLabel;
    QLabel *bpm=new QLabel;
    QPixmap *pix = new QPixmap(":/icons/settings.png");

public slots:
    void setDataNum(short int dataNum);
    void setBPMNum(short int bpmNum);
signals:

};

#endif // SPO2WIDGET_H
