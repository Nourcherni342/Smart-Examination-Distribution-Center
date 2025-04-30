#ifndef EMAIL_H
#define EMAIL_H
#include <QString>

class Email
{


public:
    Email(){};
    Email(QString, QString, QString);
    static int sendEmail(QString Email, QString object, QString body);

private:
    QString destinataire;
    QString object,body;
};

#endif // MAILING_H
