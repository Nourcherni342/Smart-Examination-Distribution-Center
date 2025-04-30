#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Feuille de style intégrée
    QString style = R"(
        QWidget {
            background-color: white;
            font-family: "Segoe UI";
            font-size: 12pt;
        }

        QPushButton {
            background-color: #007acc;
            color: white;
            border-radius: 5px;
            padding: 5px;
        }

        QPushButton:hover {
            background-color: #005f99;
        }

        QLineEdit, QComboBox {
            border: 1px solid #007acc;
            border-radius: 4px;
            padding: 4px;
            background-color: #f4faff;
        }

        QTableWidget {
            background-color: white;
            gridline-color: #007acc;
            border: 1px solid #007acc;
        }

        QHeaderView::section {
            background-color: #007acc;
            color: white;
            padding: 4px;
            border: none;
        }

        QGroupBox {
            border: 1px solid #007acc;
            border-radius: 5px;
            margin-top: 10px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 0 3px;
            color: #007acc;
            font-weight: bold;
        }
    )";

    a.setStyleSheet(style); // Appliquer le style globalement à l'application

    connection c;
    bool test = c.createconnection();
    MainWindow w;
    w.resize(1600, 900);

    if (test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
