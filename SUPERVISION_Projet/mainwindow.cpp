#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>

/*
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this); // Configuration du tableau
    ui->tableView->setFixedSize(600, 450);

    // Configuration de l'en-tête horizontal
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configuration de l'en-tête vertical
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (initDatabase()) {
        qDebug()<<"Connection ok";
        loadTableBase();
    }
    else
    {
        qDebug()<<"connection nok";
        qDebug()<<db.lastError();
    }

}

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

void MainWindow::loadTableBase() { QSqlTableModel *model = new QSqlTableModel(0,db);

    model->setTable("Mesure");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("CO2"));
    model->setHeaderData(2, Qt::Horizontal, tr("Temp"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hum"));

    ui->tableView->setModel(model);
    ui->tableView->show();
}

//Ouvre l'onglet temps réel en cliquant sur l'onglet
void MainWindow::on_actionTemps_r_l_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//Ouvre l'onglet Historique en cliquant sur l'onglet
void MainWindow::on_actionCapteur_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Ouvre l'onglet Site en cliquant sur l'onglet
void MainWindow::on_actionSite_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//Ouvre l'onglet Import_EdT en cliquant sur l'onglet
void MainWindow::on_actionImport_EdT_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//Ouvre l'onglet Visu-Courbes en cliqueant sur l'onglet
void MainWindow::on_actionVisu_Courbes_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

