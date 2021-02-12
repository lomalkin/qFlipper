#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streamparser.h"

#include <QResizeEvent>
#include <QAbstractItemView>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , parser(new StreamParser(this))
{
    ui->setupUi(this);
    connect(ui->portConnectButton, SIGNAL(clicked()), this, SLOT(onConnect()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(parser, SIGNAL(screenData(QByteArray)), ui->widget, SLOT(data(QByteArray)));
    onPortsUpdate();
    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    auto size = event->size();

    auto full_width = size.width();
    auto full_height = size.height();

    auto hor_height = ui->horizontalLayout->maximumSize().height();

    auto aspect = (float)full_width / ((full_width / FLIPPER_SCREEN_RATIO) + hor_height);


    auto width = qMin(full_width, (int)(full_height * aspect));
    auto height = qMin(full_height, (int)(full_width / aspect));

    resize(width, height);
}

void MainWindow::timerEvent(QTimerEvent *event) {
    (void)event;
    if(!serial->isOpen() && !ui->portComboBox->view()->isVisible()) {
        onPortsUpdate();
    }
}

void MainWindow::openPort() {
    qDebug() << this << "Opening port";
    auto location = ui->portComboBox->currentText();
    if (location.isEmpty())
        return;

    auto ports = QSerialPortInfo::availablePorts();
    foreach (auto port, ports) {
        if(port.systemLocation() == location) {
            serial->setPort(port);
        }
    }

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << this << "Port opened";
        serial->write("screen_stream\r");
        ui->portComboBox->setEnabled(false);
        ui->portConnectButton->setText("Disconnect");
    } else {
        qWarning() << this << "Failed to open port" << serial->error();
    }
}

void MainWindow::closePort() {
    qDebug() << this << "Closing port";
    serial->write("\0");
    serial->close();
    ui->portConnectButton->setText("Connect");
    ui->portComboBox->setEnabled(true);
    ui->widget->clearCanvas();
}

void MainWindow::onPortsUpdate() {
    auto location = ui->portComboBox->currentText();
    ui->portComboBox->clear();

    auto ports = QSerialPortInfo::availablePorts();
    foreach (auto port, ports) {
        if (port.manufacturer() != "Flipper")
            continue;
        qDebug()
            << port.portName()
            << port.manufacturer()
            << port.serialNumber()
            << port.systemLocation()
            << port.vendorIdentifier()
            << port.productIdentifier()
            ;
        ui->portComboBox->addItem(port.systemLocation());
    }
    ui->portComboBox->setCurrentText(location);
}

void MainWindow::onConnect() {
    if (serial->isOpen()) {
        closePort();
    } else {
        openPort();
    }
}

void MainWindow::onReadyRead() {
    while(serial->bytesAvailable() > 0) {
        parser->feed(serial->read(2048));
    }
}
