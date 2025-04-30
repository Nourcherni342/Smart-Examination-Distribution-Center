#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class arduino : public QObject
{
    Q_OBJECT
signals:
    void idReceived(int id); // Signal émis avec l'ID reçu
public:
    explicit arduino(QObject *parent = nullptr);
    ~arduino();

    int connect_arduino();      // Connexion au port
    int close_arduino();        // Déconnexion
    QByteArray read_from_arduino(); // Lire ce qui arrive
    bool write_to_arduino(QByteArray data); // Envoyer des données si besoin

    QString getArduinoPortName(); // Retourner le nom du port Arduino

    QSerialPort* getserialport(); // getter du port série
public slots:
    void readSerialData();

private:
    QSerialPort *serial;
    QString portname;
    bool arduino_is_available;
};

#endif // ARDUINO_H
