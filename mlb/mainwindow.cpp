#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    accessLevel = 0;

    readMLBFile("C:\\Users\\water\\Documents\\GitHub\\ST6R-MLB\\mlb\\data.txt");

    //Set Stacked Widgets
    ui->primaryStackedWidget->setCurrentIndex(0);
    ui->loginStackedWidget->setCurrentIndex(0);
    ui->bbFanStackedWidget->setCurrentIndex(0);
    ui->loginInputStackedWidget->setCurrentIndex(0);

    //Set text box entry restrictions
    ui->usernameEntry->setMaxLength(16);
    ui->passwordEntry->setMaxLength(16);

    //Populate List Widgets
    int j = 0;

    for(int i = 0; i < MLBTeamVector.size(); i++)
    {
        ui->teamNameList->addItem(MLBTeamVector[i].getTeamName());
        ui->stadiumNameList->addItem(MLBTeamVector[i].getStadiumName());
        ui->capacityList->addItem(QString::number(MLBTeamVector[i].getCapacity()));
        ui->locationList->addItem(MLBTeamVector[i].getLocation());
        ui->surfaceList->addItem(MLBTeamVector[i].getSurface());
        ui->leagueList->addItem(MLBTeamVector[i].getLeague());
        ui->dateList->addItem(QString::number(MLBTeamVector[i].getDateOpened()));
        ui->centerFieldList->addItem(QString::number(MLBTeamVector[i].getCenterField()));
        ui->typologyList->addItem(MLBTeamVector[i].getTypelogy());
        ui->roofTypeList->addItem(MLBTeamVector[i].getRoofType());
//        ui->manageRestaurantListWidget->addItem(new QListWidgetItem(QIcon(icons[i]), restaurantsVector[i].getName()));   //icons[i]), restaurantsVector[i].getName()));
//        ui->manageRestaurantListWidget->item(j)->setSizeHint(QSize(-1, 26));
        ++j;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    accessLevel = 0;
}

void MainWindow::readMLBFile(QString filePath){

    MLBTeamVector.clear();

    QFile file(filePath);

    QString nTeamName;
    QString nStadiumName;
    QString nLocation;
    QString nSurface;
    QString nLeague;
    QString nTypelogy;
    QString nRoofType;
    int nId;
    int nCapacity;
    int nDateOpened;
    int nCenterField;
//    QVector<item> nMenu;
//    float tempPrice = 0;
//    int tempId = 0;
//    int menuSize = 0;

    QTextStream in(&file);
    QString line;
//    int newDistanceSize;
//    QVector<float> tempDistance;
    int numDeleted;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    else{
        //read in nullified restaurants
        line = in.readLine();
        numDeleted = line.toInt();
        for(int i = 0; i < numDeleted; i++){
            line = in.readLine();
            deletedIndexes.push_back(line.toInt());
        }
        in.readLine(); //Number of teams
        in.readLine(); //Blank line

        while(!in.atEnd()){
            nTeamName = in.readLine();
            nId = (in.readLine()).toInt();
            nStadiumName = in.readLine();
            nLocation = in.readLine();
            nSurface = in.readLine();
            nLeague = in.readLine();
            nTypelogy = in.readLine();
            nRoofType = in.readLine();
            nCapacity = (in.readLine()).toInt();
            nDateOpened = (in.readLine()).toInt();
            nCenterField = (in.readLine()).toInt();

            line = in.readLine();
            if(line.isEmpty()){
                MLBTeam tempTeam(nTeamName,nStadiumName,nLocation,nSurface,nLeague,nTypelogy
                                 ,nRoofType,nId,nCapacity,nDateOpened,nCenterField);
                MLBTeamVector.push_back(tempTeam);
            }
        }
    }
    file.close();
}

//Primary stacked widget index 0
//Login
void MainWindow::on_enterButton_clicked(){
    ui->loginStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_loginButton_clicked(){
    bool validEntry = false;

    if(ui->usernameEntry->text() == "bbfan"){
        if(ui->passwordEntry->text() == "bbfan"){
            validEntry = true;
            accessLevel = 1;
        }
    }
    else if (ui->usernameEntry->text() == "admin") {
        if(ui->passwordEntry->text() == "admin"){
            validEntry = true;
            accessLevel = 2;
        }
    }

    if(validEntry){
        switch (accessLevel) {
        case 1: ui->bbFanStackedWidget->setCurrentIndex(0);
            break;
        case 2: ui->bbFanStackedWidget->setCurrentIndex(3);
            break;
        }
        ui->primaryStackedWidget->setCurrentIndex(1);
        ui->loginInputStackedWidget->setCurrentIndex(0);
        ui->usernameEntry->clear();
        ui->passwordEntry->clear();
    }
    else {
        ui->loginInputStackedWidget->setCurrentIndex(1);
    }
}


//Primary Stacked widget index 1
//Home (0) - bbFan Stacked Widget
void MainWindow::on_vacationButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_displayTeamsButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_logoutButton_clicked(){
    ui->loginStackedWidget->setCurrentIndex(0);
    accessLevel = 0;
    ui->primaryStackedWidget->setCurrentIndex(0);
}

//Vacation (1) - bbFan Stacked Widget
void MainWindow::on_vacationBackButton_clicked(){
    switch (accessLevel) {
    case 1: ui->bbFanStackedWidget->setCurrentIndex(0);
        break;
    case 2: ui->bbFanStackedWidget->setCurrentIndex(3);
        break;
    }
}

//Display (2) - bbFan Stacked Widget
void MainWindow::on_displayTeamsBackButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(0);
}

//Admin Home (3) - bbFan Stacked Widget
void MainWindow::on_adminVacationButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_manageTeamsButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(4);
}

void MainWindow::on_adminLogoutButton_clicked(){
    ui->loginStackedWidget->setCurrentIndex(0);
    accessLevel = 0;
    ui->primaryStackedWidget->setCurrentIndex(0);
}

//Manage (4) - bbFan Stacked Widget
void MainWindow::on_manageTeamsBackButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(3);
}
