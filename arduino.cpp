#include "arduino.h"
#include <QDebug>


arduino::arduino(QObject *parent) : QObject(parent) {
    serial = new QSerialPort(this);
    arduino_is_available = false;
    portname = "";

    // Trouver l'Arduino
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            portname = serialPortInfo.portName();
            arduino_is_available = true;
        }
    }

    // Connectez le signal readyRead au slot readSerialData
    connect(serial, &QSerialPort::readyRead, this, &arduino::readSerialData);
}
arduino::~arduino()
{
    close_arduino();
}

int arduino::connect_arduino()
{
    if (arduino_is_available) {
        serial->setPortName(portname);
        serial->open(QSerialPort::ReadWrite);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        return 0; // OK
    }
    return 1; // Arduino pas disponible
}

int arduino::close_arduino()
{
    if (serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray arduino::read_from_arduino()
{
    if (serial->isReadable())
    {
        return serial->readAll();
    }
    return QByteArray();
}

bool arduino::write_to_arduino(QByteArray data)
{
    if (serial->isWritable())
    {
        serial->write(data);
        return true;
    }
    return false;
}

QString arduino::getArduinoPortName()
{
    return portname;
}
QSerialPort* arduino::getserialport()
{
    return serial;
}
void arduino::readSerialData() {
    QByteArray data = read_from_arduino();
    QString dataString = QString::fromUtf8(data).trimmed(); // Correction d'encodage

    qDebug() << "Données reçues :" << dataString; // Affichez les données correctement

    if (!dataString.isEmpty()) {
        // Essayons de convertir la donnée en nombre
        bool ok;
        int id = dataString.toInt(&ok);

        if (ok) {
            // C'est un ID valide !
            emit idReceived(id); // On déclenche un signal vers MainWindow par exemple
        } else {
            qDebug() << "Message ignoré (pas un ID valide) :" << dataString;
        }
    } else {
        qDebug() << "Aucune donnée reçue.";
    }
}




