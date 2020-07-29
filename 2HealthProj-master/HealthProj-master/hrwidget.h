#ifndef HRWIDGET_H
#define HRWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLayout>
#include <QPixmap>
#include "labelbutton.h"

class HRWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HRWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    int dataForTCPSend;
private:
    QVBoxLayout *hrlayout =new QVBoxLayout;
    QHBoxLayout *titlebarLayout = new QHBoxLayout;
    QWidget *titlebar = new QWidget(this);
    QLabel *title = new QLabel;
    LabelButton *pixContainer = new LabelButton;
    QLabel *data = new QLabel;
    QLabel *bpm = new QLabel;
    QLabel *bpm2nothing = new QLabel;
    QPixmap *pix = new QPixmap(":/icons/settings.png");
public slots:
    void setData(short int bpmNum);
signals:

};

#endif // HRWIDGET_H
