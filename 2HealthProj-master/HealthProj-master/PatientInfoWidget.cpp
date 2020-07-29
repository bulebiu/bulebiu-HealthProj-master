#include "PatientInfoWidget.h"

PatientInfoWidget::PatientInfoWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(200,200);
//布局
    pwholeLayout->addWidget(ptopWidget);
    pwholeLayout->addWidget(pmiddle1Widget);
    pwholeLayout->addWidget(pmiddle2Widget);
    pwholeLayout->addWidget(pIDnumberWidget);
    pwholeLayout->addWidget(pbottomWidget);

    ptopLayout->addWidget(name,0,Qt::AlignRight|Qt::AlignCenter);
    ptopLayout->addWidget(nameLineEdit,0,Qt::AlignLeft|Qt::AlignCenter);
    ptopWidget->setLayout(ptopLayout);

    pmiddle1Layout->addWidget(sex,0,Qt::AlignRight|Qt::AlignCenter);
    pmiddle1Layout->addWidget(sexLineEdit,0,Qt::AlignLeft|Qt::AlignCenter);
    pmiddle1Widget->setLayout(pmiddle1Layout);

    pmiddle2Layout->addWidget(age,0,Qt::AlignRight|Qt::AlignCenter);
    pmiddle2Layout->addWidget(ageLineEdit,0,Qt::AlignLeft|Qt::AlignCenter);
    pmiddle2Widget->setLayout(pmiddle2Layout);

    pIDnumberLayout->addWidget(IDnumber,0,Qt::AlignRight|Qt::AlignCenter);
    pIDnumberLayout->addWidget(IDnumberLineEdit,0,Qt::AlignLeft|Qt::AlignCenter);
    pIDnumberWidget->setLayout(pIDnumberLayout);

    pbottomLayout->addWidget(update,0,Qt::AlignRight|Qt::AlignCenter);
    pbottomWidget->setLayout(pbottomLayout);

    this->setLayout(pwholeLayout);
//内容
    name->setText("姓名");
    sex->setText("性别");
    age->setText("年龄");
    IDnumber->setText("身份证号");
    update->setText("获取远程数据");
    nameLineEdit->setEnabled(false);
    sexLineEdit->setEnabled(false);
    ageLineEdit->setEnabled(false);
    IDnumberLineEdit->setEnabled(false);
    connect(&client, &patientInfoClient::sendInfo2Widget, this, &PatientInfoWidget::receivedData);
    connect(this, &PatientInfoWidget::getinfoSig, &client, &patientInfoClient::getinfo);
    connect(update, &QPushButton::clicked, this, &PatientInfoWidget::on_update_clicked);
    client.moveToThread(&thread);
    thread.start();
}

void PatientInfoWidget::on_update_clicked()
{
    emit getinfoSig();
}

void PatientInfoWidget::getfacilityID(QString id)
{
    client.mdeviceID = id;
    qDebug() << id;
}

void PatientInfoWidget::receivedData(QString name, QString sex, QString age, QString idNum)
{
    nameLineEdit->setText(name);
    sexLineEdit->setText(sex);
    ageLineEdit->setText(age);
    IDnumberLineEdit->setText(idNum);
}

