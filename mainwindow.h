#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QComboBox>
#include "employe.h"
#include "arduino.h"
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_afficher_clicked();
    void on_supp_clicked();
    void on_modifier_clicked();
    void on_rechercher_clicked();
    void on_pushButton_2_clicked();
    void on_pb_PDF_clicked();
    void on_pb_stat_clicked();
    void on_pushButton_ask_clicked();
    void on_pushButton_send_2_clicked();
    void on_pushButton_delete_clicked();
    QString generateRandomPassword(int length = 10);
    void on_restore_clicked();

public slots:
    void onRestorePassword();
    void readSerial(); // lecture série automatique
    void rechercherDansBase(int );

    void onIdReceivedFromArduino(int id);
    void readFromArduino();






private:
        void loadMessages();
    Ui::MainWindow *ui;                   // UI object
    employe temploye;                     // Employee instance
    //chatbot
    QMap<QString, QString> knowledgeBase;
    QString getResponse(const QString &question);
    //chatbox
    QSqlDatabase db;
    bool persistNewPassword(const QString& email, const QString& newPassword);
    arduino A;        // objet Arduino
    QTimer *timer;    // timer pour lire automatiquement
    QString arduinoBuffer;  // pour accumuler les données reçues

};

#endif // MAINWINDOW_H
