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
#include <QSqlQuery>
#include <QDateTimeAxis>
#include <QValueAxis>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /** Configuration du tableau*/
    ui->setupUi(this);
    ui->tableView->setFixedSize(800, 450);

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

QLineSeries *createSeries(const QString &name, const QVector<QPointF> &data)
{
    QLineSeries *series = new QLineSeries();
    series->setName(name);
    series->append(data);
    return series;
}

void MainWindow::setupCharts()
{
    // Récupérer les valeurs de CO2 et Température depuis la table mesure
    QSqlQuery query("SELECT co2, Temp, Hum FROM Mesure");
    QVector<QPointF> co2Data;
    QVector<QPointF> temperatureData;
    QVector<QPointF> humData;
    while (query.next()) {
        co2Data.append(QPointF(co2Data.size(), query.value(0).toFloat()));
        temperatureData.append(QPointF(temperatureData.size(), query.value(1).toFloat()));
        humData.append(QPointF(humData.size(), query.value(2).toFloat()));

    }

    // Créer les séries pour les graphiques
    QLineSeries *co2Series = createSeries("CO2", co2Data);
    QLineSeries *temperatureSeries = createSeries("Température", temperatureData);
    QLineSeries *humSeries = createSeries("Humidité", humData);

        // Définir le style des séries
        QPen pen;
    co2Series->setPen(pen);
    temperatureSeries->setColor(Qt::red);

    // Créer les graphiques
    QChart *co2Chart = new QChart();
    co2Chart->addSeries(co2Series);
    co2Chart->setTitle("Taux de CO2");

    QChart *temperatureChart = new QChart();
    temperatureChart->addSeries(temperatureSeries);
    temperatureChart->setTitle("Température");

    QChart *humChart = new QChart();
    humChart->addSeries(humSeries);
    humChart->setTitle("Humidité");

        // Créer les afficheurs de graphiques
    QChartView *co2ChartView = new QChartView(co2Chart);
    co2ChartView->setRenderHint(QPainter::Antialiasing);
    co2ChartView->setMinimumHeight(480);

    QChartView *temperatureChartView = new QChartView(temperatureChart);
    temperatureChartView->setRenderHint(QPainter::Antialiasing);
    temperatureChartView->setMinimumHeight(480);

    QChartView *humChartView = new QChartView(humChart);
    humChartView->setRenderHint(QPainter::Antialiasing);
    humChartView->setMinimumHeight(480);

    // gestion de axes et CO2
    co2Chart->setTitle("Taux de CO2");
    co2Chart->setTitleFont(QFont("Arial", 12));
    co2Chart->setTitleBrush(QBrush(Qt::black));

    QValueAxis *co2XAxis = new QValueAxis();
    co2XAxis->setTitleText("Heure");
    co2XAxis->setLabelsFont(QFont("Arial", 10));
    co2XAxis->setLabelsBrush(QBrush(Qt::black));
    co2XAxis->setRange(0, co2Data.size());
    co2Chart->addAxis(co2XAxis, Qt::AlignBottom);
    co2Series->attachAxis(co2XAxis);

    QValueAxis *co2YAxis = new QValueAxis();
    co2YAxis->setTitleText("CO2 (ppm)");
    co2YAxis->setLabelsFont(QFont("Arial", 10));
    co2YAxis->setLabelsBrush(QBrush(Qt::black));
    co2YAxis->setRange(0, 5000);
    co2Chart->addAxis(co2YAxis, Qt::AlignLeft);
    co2Series->attachAxis(co2YAxis);

    //température
    temperatureChart->setTitle("Température");
    temperatureChart->setTitleFont(QFont("Arial", 12));
    temperatureChart->setTitleBrush(QBrush(Qt::black));

    QValueAxis *temperatureXAxis = new QValueAxis();
    temperatureXAxis->setTitleText("Heure");
    temperatureXAxis->setLabelsFont(QFont("Arial", 10));
    temperatureXAxis->setLabelsBrush(QBrush(Qt::black));
    temperatureXAxis->setRange(0, temperatureData.size());
    temperatureChart->addAxis(temperatureXAxis, Qt::AlignBottom);
    temperatureSeries->attachAxis(temperatureXAxis);

    QValueAxis *temperatureYAxis = new QValueAxis();
    temperatureYAxis->setTitleText("Température (°C)");
    temperatureYAxis->setLabelsFont(QFont("Arial", 10));
    temperatureYAxis->setLabelsBrush(QBrush(Qt::black));
    temperatureYAxis->setRange(-10, 70);
    temperatureChart->addAxis(temperatureYAxis, Qt::AlignLeft);
    temperatureSeries->attachAxis(temperatureYAxis);

    //humidité
    humChart->setTitle("Humidité");
    humChart->setTitleFont(QFont("Arial", 12));
    humChart->setTitleBrush(QBrush(Qt::blue));

    QValueAxis *humXAxis = new QValueAxis();
    humXAxis->setTitleText("Heure");
    humXAxis->setLabelsFont(QFont("Arial", 10));
    humXAxis->setLabelsBrush(QBrush(Qt::black));
    humXAxis->setRange(0, humData.size());
    humChart->addAxis(humXAxis, Qt::AlignBottom);
    humSeries->attachAxis(humXAxis);

    QValueAxis *humYAxis = new QValueAxis();
    humYAxis->setTitleText("Humidité (%)");
    humYAxis->setLabelsFont(QFont("Arial", 10));
    humYAxis->setLabelsBrush(QBrush(Qt::black));
    humYAxis->setRange(0, 100);
    humChart->addAxis(humYAxis, Qt::AlignLeft);
    humSeries->attachAxis(humYAxis);

    // Créer une scroll area pour contenir les graphiques
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    // Créer un widget pour contenir les graphiques et les ajouter à la scroll area
    QWidget *chartsWidget = new QWidget();
    QVBoxLayout *chartsLayout = new QVBoxLayout(chartsWidget);
    chartsLayout->addWidget(co2ChartView);
    chartsLayout->addWidget(temperatureChartView);
    chartsLayout->addWidget(humChartView);
    chartsLayout->addStretch();
    scrollArea->setWidget(chartsWidget);

    // Ajouter la scroll area au layout de la fenêtre
    ui->gridLayout_2->addWidget(scrollArea, 0, 0, 1, 2);

}


/** slots implanté pour l'action Temps Réel*/
void MainWindow::on_actionTemps_r_l_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/** slots implanté pour l'action Temps Réel*/
void MainWindow::on_actionCapteur_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
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
    ui->stackedWidget->setCurrentIndex(1);
    setupCharts();
}
