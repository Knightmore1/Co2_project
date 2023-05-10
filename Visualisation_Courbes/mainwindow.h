/**
 * \file mainwindow.h
 * \author Théo Coufleaux
 * \version 1.2
 * \date 5 Mai 2023
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QLineSeries>


QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; } QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool initDatabase();


public slots:
    void loadTableBase();

private slots:      /** slots des onglets */
    void on_actionTemps_r_l_triggered();
    void on_actionCapteur_triggered();
    void on_actionSite_triggered();
    void on_actionImport_EdT_triggered();
    void on_actionVisu_Courbes_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QChart *chart;
    QChartView *chartView;

};

#endif // MAINWINDOW_H
