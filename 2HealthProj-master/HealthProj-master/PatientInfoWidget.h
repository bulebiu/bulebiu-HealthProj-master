#ifndef PATIENTINFOWIDGET_H
#define PATIENTINFOWIDGET_H

#include <QWidget>
#include "TCPSocket.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QThread>
#include "patientinfoclient.h"

class PatientInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PatientInfoWidget(QWidget *parent = nullptr);
    QThread thread;
    patientInfoClient client;

private:
    QWidget *ptopWidget = new QWidget;
    QWidget *pmiddle1Widget = new QWidget;
    QWidget *pmiddle2Widget = new QWidget;
    QWidget *pbottomWidget = new QWidget;
    QWidget *pIDnumberWidget = new QWidget;
    QLabel *name = new QLabel;
    QLabel *sex = new QLabel;
    QLabel *age = new QLabel;
    QLabel *IDnumber = new QLabel;
    QLineEdit *nameLineEdit = new QLineEdit;
    QLineEdit *sexLineEdit = new QLineEdit;
    QLineEdit *ageLineEdit = new QLineEdit;
    QLineEdit *IDnumberLineEdit = new QLineEdit;
    QPushButton *update = new QPushButton;

    QVBoxLayout *pwholeLayout = new QVBoxLayout;
    QHBoxLayout *ptopLayout = new QHBoxLayout;
    QHBoxLayout *pmiddle1Layout = new QHBoxLayout;
    QHBoxLayout *pmiddle2Layout = new QHBoxLayout;
    QHBoxLayout *pbottomLayout = new QHBoxLayout;
    QHBoxLayout *pIDnumberLayout = new QHBoxLayout;


public slots:
    void on_update_clicked();
    void getfacilityID(QString id);
    void receivedData(QString name, QString sex, QString age, QString idNum);

signals:
    void getinfoSig();
};

#endif // PATIENTINFOWIDGET_H
