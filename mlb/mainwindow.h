#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include "mlbteam.h"
#include <QTextStream>
#include <QFile>

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
    //parcers
    void readMLBFile(QString filePath);

    //Primary stacked widget index 0
    //Login
    void on_enterButton_clicked();
    void on_loginButton_clicked();

    //Primary Stacked widget index 1
    //Home (0)
    void on_vacationButton_clicked();
    void on_displayTeamsButton_clicked();
    void on_logoutButton_clicked();

    //Vacation (1)
    void on_vacationBackButton_clicked();

    //Display (2)
    void on_displayTeamsBackButton_clicked();

    //Admin Home (3)
    void on_adminVacationButton_clicked();
    void on_manageTeamsButton_clicked();
    void on_adminLogoutButton_clicked();

    //Manage (4)
    void on_manageTeamsBackButton_clicked();

private:
    Ui::MainWindow *ui;
    int accessLevel; //0 is default, 1 is bbFan, 2 is administrator
    QVector<MLBTeam> MLBTeamVector;
    QVector<int> nullifiedIndexes;
    QVector<int> deletedIndexes;
};

#endif // MAINWINDOW_H
