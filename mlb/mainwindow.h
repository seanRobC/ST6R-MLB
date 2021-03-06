#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include "mlbteam.h"
#include <QTextStream>
#include <QFile>
#include <QTableWidget>
#include "vacation.h"

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
    void readMLBFile2(QString filePath);

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
    void on_checkAllButton_clicked();
    void on_selectTeamsListWidget_itemChanged(QListWidgetItem*item);
    void on_takeTripButton_clicked();
    void on_optimizeTripButton_clicked();
    void on_vacationBackButton_clicked();

    //Display (2)
    void on_openRoofOnly_stateChanged(int state);
    void on_leagueBox_activated(int index);
    void on_sortTypeBox_activated(int index);
    void on_displayTeamsBackButton_clicked();
    void on_displayTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    //Admin Home (3)
    void on_adminVacationButton_clicked();
    void on_manageTeamsButton_clicked();
    void on_adminLogoutButton_clicked();

    //Manage (4)
    void on_openRoofOnly_2_stateChanged(int state);
    void on_leagueBox_2_activated(int index);
    void on_sortTypeBox_2_activated(int index);
    void on_addTeamsButton_clicked();
    void on_deleteTeamButton_clicked();
    void on_manageTeamsBackButton_clicked();
    void on_addItemButton_clicked();
    void on_deleteItemButton_clicked();
    void on_souvenirList_2_itemDoubleClicked(QListWidgetItem *item);
    void on_priceList_2_itemDoubleClicked(QListWidgetItem *item);
    void on_addItemConfirmationBox_accepted();
    void on_manageTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void on_addItemConfirmationBox_rejected();
    void on_priceList_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_souvenirList_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_manageTable_itemDoubleClicked(QTableWidgetItem *item);

    //Helpers
    void updateDisplay(QVector<int> vec);
    void updateTable(QVector<int> vec);
    bool isFloatNumber(const QString& Qstring);
    bool isIntNumber(const QString& Qstring);

private:
    Ui::MainWindow *ui;
    int accessLevel; //0 is default, 1 is bbFan, 2 is administrator
    QVector<MLBTeam> MLBTeamVector;
    QVector<int> nullifiedIndexes;
    QVector<int> deletedIndexes;
    int filesAdded;
    int leagueSetting;
    bool roofExclude;
    vacation currentVacation;
};

#endif // MAINWINDOW_H
