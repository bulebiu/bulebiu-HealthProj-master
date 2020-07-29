#ifndef QWIDGETECGCOM_H
#define QWIDGETECGCOM_H

#include <QWidget>

class QWidgetEcgCom : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetEcgCom(QWidget *parent = nullptr);
public slots:
    void ecgBpmCalc();

signals:
    void sendbpm(int data);

};

#endif // QWIDGETECGCOM_H
