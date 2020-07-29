#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLayout>
#include "labelbutton.h"
#include "DeviceSettingsWidget.h"
#include "TCPSettingsWidget.h"
#include "PatientInfoWidget.h"
#include "client.h"

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    QHBoxLayout *layout = new QHBoxLayout(this);

    QLabel *deviceAndNote = new QLabel(this);
    QLabel *peopleIcon = new QLabel(this);
    LabelButton *cloudIcon = new LabelButton(this);
    LabelButton *exclamationIcon = new LabelButton(this);
    LabelButton *peopleInfoIcon = new LabelButton(this);
    LabelButton *scaleIcon = new LabelButton(this);

    QPixmap *peoplePNG = new QPixmap(":/icons/people.png");
    QPixmap *exclamationPNG = new QPixmap(":/icons/exclamation.png");
    QPixmap *scalePNG = new QPixmap(":/icons/scale.png");
    QPixmap *cloudPNG = new QPixmap(":/icons/cloud.png");
    QPixmap *infoPNG = new QPixmap(":/icons/info.png");

    DeviceSettingsWidget *ds = new DeviceSettingsWidget;
    TCPSettingsWidget *tcpsettings = new TCPSettingsWidget;
    PatientInfoWidget *pinfo = new PatientInfoWidget;
    bool isfullscreen = false;

public slots:
    void openDSWindow();
    void openTCPWindow();
    void openINFOWindow();
    void setFullscreen();
    void middleTCPSlot(QString ip, quint16 port);
    void setNotes(QString note);
signals:
    void enablefullscreen();
    void disablefullscreen();
    void middleTCP(QString ip, quint16 port);
};

#endif // TITLEBAR_H
