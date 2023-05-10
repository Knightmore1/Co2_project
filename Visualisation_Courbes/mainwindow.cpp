/**
 * \file mainwindow.cpp
 * \author Théo Coufleaux
 * \version 1.2
 * \date 5 Mai 2023
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /** Configuration du tableau*/
    ui->setupUi(this);
    ui->tableView->setFixedSize(600, 450);

    /** Configuration de l'en-tête horizontal*/
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /** Configuration de l'en-tête vertical*/
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /** test pour liaison à la base de données*/
    if (initDatabase()) {
        qDebug()<<"Connection ok";
        loadTableBase();
    }
    else
    {
        qDebug()<<"connection nok";
        qDebug()<<db.lastError();
    }
    /** Création de Courbes pour la Visu-Courbes*/
    chart = new QChart();
    QLineSeries *series = new QLineSeries();

    chartView = new QChartView(chart);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Taux de Co2");

    ui->gridLayout->addWidget(chartView, 3, 2);

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

}
/** Connexion à la base de données*/
    MainWindow::~MainWindow() { delete ui; }

    bool MainWindow::initDatabase()
    {
        db = QSqlDatabase::addDatabase("QMARIADB");
        db.setDatabaseName("co2");
        db.setHostName("172.20.233.66");
        db.setUserName("supervision");
        db.setPassword("supervision");
        return db.open();
    }
    /** Importation de la base de données*/
void MainWindow::loadTableBase() {

    model = new QSqlTableModel(0,db);
    model->setTable("Mesure");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("CO2"));
    model->setHeaderData(2, Qt::Horizontal, tr("Temp"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hum"));

    ui->tableView->setModel(model);
    ui->tableView->show();
}


/** slots implanté pour l'action Temps Réel*/
    void MainWindow::on_actionTemps_r_l_triggered()
    {
        ui->stackedWidget->setCurrentIndex(0);
    }

    /** slots implanté pour l'action Temps Réel*/
    void MainWindow::on_actionCapteur_triggered()
    {
        ui->stackedWidget->setCurrentIndex(1);
    }

    /** slots implanté pour l'action actionSite*/
void MainWindow::on_actionSite_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/** slots implanté pour l'action Import-EdT*/
void MainWindow::on_actionImport_EdT_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/** slots implanté pour l'action Visu-Courbes*/
void MainWindow::on_actionVisu_Courbes_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}
