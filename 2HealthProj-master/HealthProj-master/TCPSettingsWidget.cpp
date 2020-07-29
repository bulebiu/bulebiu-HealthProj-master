#include "TCPSettingsWidget.h"

TCPSettingsWidget::TCPSettingsWidget(QWidget *parent) : QWidget(parent)
{
    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(ipEdit);
    portLayout->addWidget(portLabel);
    portLayout->addWidget(portEdit);
    buttonLayout->addWidget(testBtn);
    buttonLayout->addWidget(applyBtn);
    all->addLayout(ipLayout);
    all->addLayout(portLayout);
    all->addLayout(buttonLayout);
    this->setLayout(all);

    ipLabel->setText("IP:");
    portLabel->setText("PORT:");
    testBtn->setText("测试");
    applyBtn->setText("应用");

    connect(applyBtn, &QPushButton::clicked, this, &TCPSettingsWidget::setTCPIP);
    connect(testBtn, &QPushButton::clicked, this, &TCPSettingsWidget::testTCPIP);
    connect(this, &TCPSettingsWidget::testSig, socketForTest, &TCPSocket::testTCPIP);
    connect(socketForTest, &TCPSocket::testSuccess, this, &TCPSettingsWidget::successTest);
    connect(socketForTest, &TCPSocket::testFailed, this, &TCPSettingsWidget::failTest);
    socketForTest->moveToThread(&thread);
    thread.start();
}

void TCPSettingsWidget::setTCPIP()
{
    emit tcpipChanged(ipEdit->text(), portEdit->text().toUInt());
}

void TCPSettingsWidget::testTCPIP()
{
    emit testSig(ipEdit->text(), portEdit->text().toUInt());
}

void TCPSettingsWidget::successTest()
{
    QMessageBox::information(NULL, "Success", "成功");
}

void TCPSettingsWidget::failTest()
{
    QMessageBox::information(NULL, "Failed", "失败");
}

void TCPSettingsWidget::setWindowSize(int w, int h)
{
    this->resize(w, h);
}
