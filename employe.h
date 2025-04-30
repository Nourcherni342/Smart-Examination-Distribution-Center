#ifndef employe_H
#define employe_H

#include <QDialog>
#include<QSqlQuery>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class employe
{
    QString nom,prenom,spec,genre,adresseemploye,presence,id_employe;
        int tel,salaire;
public:
    employe();
    employe(QString,QString,QString,int,int,QString,QString,QString,QString);


    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getspecialite() const { return spec; }
    QString getGenre() const { return genre; }
    QString getAdresseemploye() const { return adresseemploye; }
    QString getPresence() const { return presence; }
    int getTel() const { return tel; }
    int getSalaire() const { return salaire; }
    QString getid() const { return id_employe; }



    void setNom(const QString &n) { nom = n; }
    void setPrenom(const QString &pn) { prenom = pn; }
    void setspecialite(const QString &s) { spec = s; }
    void setTel(int t) { tel = t; }
    void setSalaire(int s) { salaire = s; }
    void setGenre(const QString &g) { genre = g; }
    void setAdresseemploye(const QString &ad) { adresseemploye = ad; }
    void setPresence(const QString &p) { presence = p; }
    void setId(const QString &i) { id_employe = i; }




    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,int,int,QString,QString,QString,QString);
    void rechercher(QTableView *table,QString cas );

};

#endif // employe_H
