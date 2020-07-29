#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QEvent>

class LabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit LabelButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
signals:
    void clicked();
};

#endif // LABELBUTTON_H
