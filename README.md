# Co2_project
1-Besoins du client:
  Supervision des données 
  Visualition des données en courbes 
  Import des Emploi du temps, salle de cours et heure de cours
  
2-Fonctionnalités:
  






3-Maquette IHM:


![image](https://user-images.githubusercontent.com/123626891/224353463-ee26173e-cb6e-4eae-9f1b-0f576f545a75.png)




Code mainwindow.cpp:

#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QDebug>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Configuration du tableau
    ui->tableView->setFixedSize(600, 450);

    // Configuration de l'en-tête horizontal
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configuration de l'en-tête vertical
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (initDatabase()) qDebug()<<"Connection ok";
    else qDebug()<<"connection nok";
    loadTableBase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initDatabase()
{
    db = QSqlDatabase::addDatabase("QMARIADB");
    db.setDatabaseName("co2");
    db.setHostName("172.20.233.44");
    db.setUserName("supervision");
    db.setPassword("supervision");
    return db.open();
}

void MainWindow::loadTableBase()
{
    QSqlTableModel *model = new QSqlTableModel(0,db);


    model->setTable("Mesure");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("CO2"));
    model->setHeaderData(2, Qt::Horizontal, tr("Temp"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hum"));

    ui->tableView->setModel(model);
    ui->tableView->show();
}

void MainWindow::on_actionTemps_r_l_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionHistorique_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionSite_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionImport_EdT_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_clicked()
{
    loadTableBase();
}

mainwindow.h :

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool initDatabase();
    void loadTableBase();

private slots:
    void on_actionTemps_r_l_triggered();
    void on_actionHistorique_triggered();
    void on_actionSite_triggered();
    void on_actionImport_EdT_triggered();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

};
#endif // MAINWINDOW_H


