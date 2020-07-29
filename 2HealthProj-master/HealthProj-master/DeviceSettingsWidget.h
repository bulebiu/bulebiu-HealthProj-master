#ifndef DEVICESETTINGSWIDGET_H
#define DEVICESETTINGSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLayout>
#include <QNetworkInterface>
#include "GetSerial.h"

class DeviceSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceSettingsWidget(QWidget *parent = nullptr, GetSerial *gs_ = NULL);
    GetSerial *gs;

signals:

private:
    QLabel *deviceID = new QLabel;
    QLabel *serialPortLable = new QLabel;
    QLabel *notesLabel = new QLabel;

    QLineEdit *deviceIDEdit = new QLineEdit;
    QPushButton *serialComSet = new QPushButton;
    QPushButton *serialComGet = new QPushButton;
    QComboBox *serialChosen = new QComboBox;
    QLineEdit *notesEdit = new QLineEdit;
    QPushButton *notesButton = new QPushButton;

    QVBoxLayout *allLayout = new QVBoxLayout;
    QHBoxLayout *deviceLayout = new QHBoxLayout;
    QHBoxLayout *badLayout = new QHBoxLayout;
    QHBoxLayout *serialPortLayout = new QHBoxLayout;
    QHBoxLayout *notesLayout = new QHBoxLayout;
    
public slots:
    void setComNum();
    void getComs();
    void setNotes();

signals:
    void noteChangeSig(QString note);
};

#endif // DEVICESETTINGSWIDGET_H
