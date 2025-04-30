#include "email.h"
#include <QSslSocket>
#include <QDebug>
#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>

int Email::sendEmail(QString dist, QString obj, QString bdy)
{
    // Check SSL support
    qDebug() << "sslLibraryBuildVersionString:" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "sslLibraryVersionNumber:" << QSslSocket::sslLibraryVersionNumber();
    qDebug() << "supportsSsl:" << QSslSocket::supportsSsl();
    qDebug() << QCoreApplication::libraryPaths();

    // Email configuration
    const QString smtpServer = "smtp.gmail.com";
    const int smtpPort = 465;
    const QString username = "badi3tlijani12@gmail.com";
    const QString password = "pdsz wbbe ooba pmhg";
    const QString from = "badi3tlijani12@gmail.com";
    const QString to = dist;
    const QString subject = obj;
    const QString body = bdy;

    QSslSocket socket;

    // Connect to server
    socket.connectToHostEncrypted(smtpServer, smtpPort);
    if (!socket.waitForConnected(5000)) {
        qDebug() << "Error connecting to the server:" << socket.errorString();
        return -1;
    }
    if (!socket.waitForReadyRead(5000)) {
        qDebug() << "Error reading from server:" << socket.errorString();
        return -1;
    }
    qDebug() << "Connected to the server.";

    // SMTP protocol sequence
    auto writeAndWait = [&socket](const QByteArray &data) -> bool {
        socket.write(data);
        if (!socket.waitForBytesWritten(5000)) {
            qDebug() << "Error writing to server:" << socket.errorString();
            return false;
        }
        if (!socket.waitForReadyRead(5000)) {
            qDebug() << "Error reading from server:" << socket.errorString();
            return false;
        }
        return true;
    };

    // SMTP commands
    if (!writeAndWait("EHLO localhost\r\n")) return -1;
    if (!writeAndWait("AUTH LOGIN\r\n")) return -1;
    if (!writeAndWait(username.toUtf8().toBase64() + "\r\n")) return -1;
    if (!writeAndWait(password.toUtf8().toBase64() + "\r\n")) return -1;
    if (!writeAndWait("MAIL FROM:<" + from.toUtf8() + ">\r\n")) return -1;
    if (!writeAndWait("RCPT TO:<" + to.toUtf8() + ">\r\n")) return -1;
    if (!writeAndWait("DATA\r\n")) return -1;

    // Email headers and body
    QByteArray emailData;
    emailData.append("From: " + from.toUtf8() + "\r\n");
    emailData.append("To: " + to.toUtf8() + "\r\n");
    emailData.append("Subject: " + subject.toUtf8() + "\r\n");
    emailData.append("\r\n");
    emailData.append(body.toUtf8() + "\r\n");
    emailData.append(".\r\n");

    if (!writeAndWait(emailData)) return -1;
    if (!writeAndWait("QUIT\r\n")) return -1;

    qDebug() << "Email sent successfully.";
    socket.close();
    return 0;
}
