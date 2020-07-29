#ifndef STWIDGET_H
#define STWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLayout>
#include "labelbutton.h"

class STWidget : public QWidget
{
    Q_OBJECT
public:
    explicit STWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    int dataForTCPSend1;
    int dataForTCPSend2;
    int dataForTCPSend3;
private:
    QVBoxLayout *stlayout = new QVBoxLayout;
    QHBoxLayout *titleBarLayout = new QHBoxLayout;
    QWidget *strightWidget =new QWidget;
    QWidget *titleBar = new QWidget;
    QLabel *title = new QLabel;
    LabelButton *pixContainer = new LabelButton;
    QLabel *stl1 = new QLabel;
    QLabel *stl2 = new QLabel;
    QLabel *pvcs = new QLabel;
    QPixmap *pix = new QPixmap(":/icons/settings.png");

public slots:
    void setST1Num(short int st1Num);
    void setST2Num(short int st2Num);
    void setPVCNum(short int pvcsNum);
signals:

};

#endif // STWIDGET_H
