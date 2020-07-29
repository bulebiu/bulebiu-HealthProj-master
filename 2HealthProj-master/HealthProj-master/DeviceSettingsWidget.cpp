#include "DeviceSettingsWidget.h"

DeviceSettingsWidget::DeviceSettingsWidget(QWidget *parent, GetSerial *gs_) : QWidget(parent), gs(gs_)
{
    deviceLayout->addWidget(deviceID);
    deviceLayout->addWidget(deviceIDEdit);
    serialPortLayout->addWidget(serialPortLable);
    serialPortLayout->addWidget(serialChosen);
    serialPortLayout->addWidget(serialComGet);
    serialPortLayout->addWidget(serialComSet);
    notesLayout->addWidget(notesLabel);
    notesLayout->addWidget(notesEdit);
    notesLayout->addWidget(notesButton);
    allLayout->addStretch(2);
    allLayout->addLayout(deviceLayout);
    allLayout->addStretch(1);
    allLayout->addLayout(notesLayout);
    allLayout->addStretch(1);
    allLayout->addLayout(serialPortLayout);
    allLayout->addStretch(1);
    allLayout->addStretch(2);

    this->setLayout(allLayout);

    deviceID->setText("设备序列号：");
    deviceIDEdit->setText(QNetworkInterface::allInterfaces()[0].hardwareAddress().split(":").join("0"));
    deviceIDEdit->setEnabled(false);

    serialPortLable->setText("串口选择：");
    serialComGet->setText("获取");
    serialComSet->setText("设置");

    notesLabel->setText("备注:");
    notesEdit->setText("001");
    notesButton->setText("修改");

    connect(notesButton, &QPushButton::clicked, this, &DeviceSettingsWidget::setNotes);
    connect(serialComSet, &QPushButton::clicked, this, &DeviceSettingsWidget::setComNum);
    connect(serialComGet, &QPushButton::clicked, this, &DeviceSettingsWidget::getComs);
}

void DeviceSettingsWidget::setComNum()
{
    gs->close();
    gs->portName = serialChosen->currentText();
    QMessageBox::information(NULL, "Success", "成功");
    gs->connectPort();
}

void DeviceSettingsWidget::getComs()
{
    QList<QString> coms = gs->getPortsName();
    for(int i=0;i<coms.length();i++)
    {
        serialChosen->addItem(coms[i]);
    }
}

void DeviceSettingsWidget::setNotes()
{
    emit noteChangeSig(notesEdit->text());
}



