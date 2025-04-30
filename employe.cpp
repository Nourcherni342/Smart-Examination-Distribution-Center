#include "employe.h"
#include <QSqlError>

employe::employe()
{
    id_employe =" ";
    nom =" ";
    prenom =" ";
    tel = 0;
    salaire =0;
    genre =" ";
    adresseemploye =" ";
    presence =" ";
    spec = " ";
}
employe::employe(QString id_employe,QString nom,QString prenom,int tel,int salaire,QString genre,QString adresseemploye,QString presence,QString spec)
{
    this->id_employe =id_employe;
    this->nom =nom;
    this->prenom =prenom;
    this->tel =tel;
    this->salaire =salaire;
    this->genre =genre;
    this->adresseemploye =adresseemploye;
    this->presence =presence;
    this->spec =spec;
}

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (id_employe, nom, prenom, tel, salaire, genre, adresseemploye, presence, spec) "
                  "VALUES (:id_employe, :nom, :prenom, :tel, :salaire, :genre, :adresseemploye, :presence, :spec)");

    query.bindValue(":id_employe", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", tel);
    query.bindValue(":salaire", salaire);
    query.bindValue(":genre", genre);
    query.bindValue(":adresseemploye", adresseemploye);
    query.bindValue(":presence", presence);
    query.bindValue(":spec", spec);

    return query.exec();
}
QSqlQueryModel *employe::afficher()
{
 QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("select *from employe");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("TELEPHONE"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("SALAIRE"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("GENRE"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("ADRESSE"));
 model->setHeaderData(7, Qt::Horizontal,QObject::tr("PRESENCE"));
 model->setHeaderData(8, Qt::Horizontal,QObject::tr("spec"));

 return model;
}

bool employe::supprimer(QString cc)
{
    QSqlQuery query;
    query.prepare("Delete from employe where id_employe = :id_employe ");
    query.bindValue(":id_employe",cc);
    return query.exec();

}

bool employe::modifier(QString id_employe, QString nom, QString prenom, int tel, int salaire, QString genre, QString adresseemploye, QString presence, QString specialite)
{
    QSqlQuery qry;
    qry.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, tel = :tel, salaire = :salaire, genre = :genre, "
                "adresseemploye = :adresseemploye, presence = :presence, spec = :spec WHERE id_employe = :id_employe");

    qry.bindValue(":id_employe", id_employe);
    qry.bindValue(":nom", nom);
    qry.bindValue(":prenom", prenom);
    qry.bindValue(":tel", tel);
    qry.bindValue(":salaire", salaire);
    qry.bindValue(":genre", genre);
    qry.bindValue(":adresseemploye", adresseemploye);
    qry.bindValue(":presence", presence);
    qry.bindValue(":spec", spec);

    return qry.exec();
}

void employe::rechercher(QTableView *table, QString cas)
{
    table->setModel(nullptr);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Requête SQL avec LIKE pour permettre une recherche partielle
    query.prepare("SELECT * FROM employe "
                  "WHERE id_employe LIKE :val "
                  "OR salaire LIKE :val "
                  "OR nom LIKE :val "
                  "OR prenom LIKE :val");

    query.bindValue(":val", "%" + cas + "%");  // le même critère appliqué à plusieurs colonnes

    if (query.exec())
    {
        model->setQuery(query);
        if (model->rowCount() > 0)
        {
            table->setModel(model);
            table->show();
        }
        else
        {
            qDebug() << "Aucun résultat trouvé pour :" << cas;
        }
    }
    else
    {
        qDebug() << "Erreur de requête :" << query.lastError().text();
    }
}



