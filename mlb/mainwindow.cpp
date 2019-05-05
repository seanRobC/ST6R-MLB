#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QtDebug>
#include "QString"
#include "QChar"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    accessLevel = 0;
    filesAdded = -1;
    leagueSetting = 0;

    readMLBFile("C:\\Users\\water\\Documents\\GitHub\\ST6R-MLB\\mlb\\data.txt");

    //Set Stacked Widgets
    ui->primaryStackedWidget->setCurrentIndex(0);
    ui->loginStackedWidget->setCurrentIndex(0);
    ui->bbFanStackedWidget->setCurrentIndex(0);
    ui->loginInputStackedWidget->setCurrentIndex(0);
    ui->addItemWidget->setCurrentIndex(0);
    ui->centerFieldStacked_2->setCurrentIndex(0);

    //Set text box entry restrictions
    ui->usernameEntry->setMaxLength(16);
    ui->passwordEntry->setMaxLength(16);
    ui->itemNameEntry->setMaxLength(40);
    ui->itemPriceEntry->setMaxLength(8);

    //Populate List Widgets
    int j = 0;

    QStringList title;
    title <<"Team Name"<<"Stadium Name"<<"Capacity"<<"Location"<<"Surface"<<"League"<<"Date Opened"<<"Center Field Dist."<<"Typology"<<"Roof Type";
    ui->manageTable->setColumnCount(10);
    ui->manageTable->setHorizontalHeaderLabels(title);

    for(int i = 0; i < MLBTeamVector.size(); i++)
    {
        ui->manageTable->insertRow(ui->manageTable->rowCount());
        ui->manageTable->setItem(i,0,new QTableWidgetItem(MLBTeamVector[i].getTeamName()));
        ui->manageTable->setItem(i,1,new QTableWidgetItem(MLBTeamVector[i].getStadiumName()));
        ui->manageTable->setItem(i,2,new QTableWidgetItem((QString::number(MLBTeamVector[i].getCapacity()))));
        ui->manageTable->setItem(i,3,new QTableWidgetItem(MLBTeamVector[i].getLocation()));
        ui->manageTable->setItem(i,4,new QTableWidgetItem(MLBTeamVector[i].getSurface()));
        ui->manageTable->setItem(i,5,new QTableWidgetItem(MLBTeamVector[i].getLeague()));
        ui->manageTable->setItem(i,6,new QTableWidgetItem((QString::number(MLBTeamVector[i].getDateOpened()))));
        ui->manageTable->setItem(i,7,new QTableWidgetItem((QString::number(MLBTeamVector[i].getCenterField()))+" ("+QString::number(round(MLBTeamVector[i].getCenterField()*.3048))+"m)"));
        ui->manageTable->setItem(i,8,new QTableWidgetItem(MLBTeamVector[i].getTypelogy()));
        ui->manageTable->setItem(i,9,new QTableWidgetItem(MLBTeamVector[i].getRoofType()));

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
    QStringList title2;
    title2 <<"Default"<<"Team Name"<<"Stadium Name"<<"Capacity"<<"Date Opened"<<"Max Center Field Dist."<<"Min Center Field Dist."<<"Typology";
    QStringList title3;
    title3 <<"All"<<"National"<<"American";
    ui->sortTypeBox_2->addItems(title2);
    ui->leagueBox_2->addItems(title3);
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
                tempTeam.addMenuItem("Baseball cap", 22.99);
                tempTeam.addMenuItem("Baseball bat", 89.39);
                tempTeam.addMenuItem("Team pennant", 17.99);
                tempTeam.addMenuItem("Autographed baseball", 25.99);
                tempTeam.addMenuItem("Team jersey", 199.99);
                MLBTeamVector.push_back(tempTeam);
            }
        }
    }
    file.close();
}

void MainWindow::readMLBFile2(QString filePath){
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
    QTextStream in(&file);
    QString line;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    else{
        while(!in.atEnd()){
            nTeamName = in.readLine();
            nId = (in.readLine()).toInt();
            nStadiumName = in.readLine();
            nCapacity = (in.readLine()).toInt();
            nLocation = in.readLine();
            nSurface = in.readLine();
            nLeague = in.readLine();
            nDateOpened = (in.readLine()).toInt();
            nCenterField = (in.readLine()).toInt();
            nTypelogy = in.readLine();
            nRoofType = in.readLine();

            line = in.readLine();
            if(line.isEmpty()){
                MLBTeam tempTeam(nTeamName,nStadiumName,nLocation,nSurface,nLeague,nTypelogy
                                 ,nRoofType,nId,nCapacity,nDateOpened,nCenterField);
                tempTeam.addMenuItem("Baseball cap", 22.99);
                tempTeam.addMenuItem("Baseball bat", 89.39);
                tempTeam.addMenuItem("Team pennant", 17.99);
                tempTeam.addMenuItem("Autographed baseball", 25.99);
                tempTeam.addMenuItem("Team jersey", 199.99);
                MLBTeamVector.push_back(tempTeam);
            }
        }
    }
    file.close();

    ui->manageTable->insertRow(ui->manageTable->rowCount());
    ui->manageTable->setItem(MLBTeamVector.size()-1,0,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getTeamName()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,1,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getStadiumName()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,2,new QTableWidgetItem((QString::number(MLBTeamVector[MLBTeamVector.size()-1].getCapacity()))));
    ui->manageTable->setItem(MLBTeamVector.size()-1,3,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getLocation()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,4,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getSurface()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,5,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getLeague()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,6,new QTableWidgetItem((QString::number(MLBTeamVector[MLBTeamVector.size()-1].getDateOpened()))));
    ui->manageTable->setItem(MLBTeamVector.size()-1,7,new QTableWidgetItem((QString::number(MLBTeamVector[MLBTeamVector.size()-1].getCenterField()))+" ("+QString::number(round(MLBTeamVector[MLBTeamVector.size()-1].getCenterField()*.3048))+"m)"));
    ui->manageTable->setItem(MLBTeamVector.size()-1,8,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getTypelogy()));
    ui->manageTable->setItem(MLBTeamVector.size()-1,9,new QTableWidgetItem(MLBTeamVector[MLBTeamVector.size()-1].getRoofType()));
    filesAdded =1;
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
void MainWindow::on_leagueBox_2_activated(int index){
    switch(index){
    case 0: leagueSetting = 0;
            ui->sortTypeBox_2->setCurrentIndex(0);
            on_sortTypeBox_2_activated(ui->sortTypeBox_2->currentIndex());
        break;
    case 1: leagueSetting = 1;
            ui->sortTypeBox_2->setCurrentIndex(0);
            on_sortTypeBox_2_activated(ui->sortTypeBox_2->currentIndex());
        break;
    case 2: leagueSetting = 2;
            ui->sortTypeBox_2->setCurrentIndex(0);
            on_sortTypeBox_2_activated(ui->sortTypeBox_2->currentIndex());
        break;
    }
}

void MainWindow::on_sortTypeBox_2_activated(int index){
    QVector<int> vec;
    QVector<QString> temp;

    int impNum = 0;
    int errorFlag = 0;

    if(leagueSetting == 0){
        impNum = MLBTeamVector[0].getCenterField();
    }
    else if (leagueSetting == 1) {
        int o =0;
        while (MLBTeamVector[o].getLeague()!="National"&&o<MLBTeamVector.size()) {
            o++;
        }
        if(o < MLBTeamVector.size()){
            impNum = MLBTeamVector[o].getCenterField();
        }
        else {
            errorFlag = 1;
        }
    }
    else if (leagueSetting == 2) {
        int o =0;
        while (MLBTeamVector[o].getLeague()!="American"&&o<MLBTeamVector.size()) {
            o++;
        }
        if(o < MLBTeamVector.size()){
            impNum = MLBTeamVector[o].getCenterField();
        }
        errorFlag = 1;
    }

    ui->centerFieldStacked_2->setCurrentIndex(0);

    switch (index) {
    case 0: for(int i = 0;i<MLBTeamVector.size();i++){
                if(leagueSetting == 0)
                    vec.push_back(i);
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague() == "National"){
                        vec.push_back(i);
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague() == "American"){
                        vec.push_back(i);
                    }
                }
            }
            updateTable(vec);
        break;
    case 1: if(leagueSetting == 0){
                vec.push_back(0);
                for (int i = 1;i<MLBTeamVector.size();i++) {
                    int c = MLBTeamVector[i].getTeamName()[0].toUpper().unicode();
                    bool spotF = false;
                    int k = 0;
                    while (!spotF && k < vec.size()) {
                        if(c < MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()){
                            vec.insert(k,i);
                            spotF = true;
                        }
                        else if (c == MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()) {
                            int j = 1;
                            while (!spotF && j < MLBTeamVector[i].getTeamName().size()&& j < MLBTeamVector[vec[k]].getTeamName().size()) {
                                if(MLBTeamVector[i].getTeamName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (MLBTeamVector[i].getTeamName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode())
                                    j++;
                                else {
                                    if(k+1 == vec.size()){
                                        vec.insert(k+1,i);
                                        spotF = true;
                                    }
                                    else if (MLBTeamVector[k+1].getTeamName()[0].toUpper().unicode() != MLBTeamVector[i].getTeamName()[0].toUpper().unicode()) {
                                        vec.insert(k+1,i);
                                        spotF = true;
                                    }
                                    else {
                                        k++;
                                    }
                                }
                            }
                            if(!spotF){
                                if(MLBTeamVector[i].getTeamName().size() < MLBTeamVector[vec[k]].getTeamName().size()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if(MLBTeamVector[i].getTeamName().size() > MLBTeamVector[vec[k]].getTeamName().size()){
                                    vec.insert(k+1,i);
                                    spotF = true;
                                }
                            }
                        }
                        else {
                            k++;
                        }
                    }
                    if(!spotF){
                        vec.insert(k,i);
                        spotF = true;
                    }
                }
            }
            else if (leagueSetting == 1) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "National" && o <MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                    for (int i = o+1;i<MLBTeamVector.size();i++) {
                        if(MLBTeamVector[i].getLeague() == "National"){
                            int c = MLBTeamVector[i].getTeamName()[0].toUpper().unicode();
                            bool spotF = false;
                            int k = 0;
                            while (!spotF && k < vec.size()) {
                                if(c < MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (c == MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()) {
                                    int j = 1;
                                    while (!spotF && j < MLBTeamVector[i].getTeamName().size()&& j < MLBTeamVector[vec[k]].getTeamName().size()) {
                                        if(MLBTeamVector[i].getTeamName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if (MLBTeamVector[i].getTeamName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode())
                                            j++;
                                        else {
                                            if(k+1 == vec.size()){
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else if (MLBTeamVector[k+1].getTeamName()[0].toUpper().unicode() != MLBTeamVector[i].getTeamName()[0].toUpper().unicode()) {
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else {
                                                k++;
                                            }
                                        }
                                    }
                                    if(!spotF){
                                        if(MLBTeamVector[i].getTeamName().size() < MLBTeamVector[vec[k]].getTeamName().size()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if(MLBTeamVector[i].getTeamName().size() > MLBTeamVector[vec[k]].getTeamName().size()){
                                            vec.insert(k+1,i);
                                            spotF = true;
                                        }
                                    }
                                }
                                else {
                                    k++;
                                }
                            }
                            if(!spotF){
                                vec.insert(k,i);
                                spotF = true;
                            }
                        }
                    }
                }
            }
            else if (leagueSetting == 2) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "American" && o <MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                    for (int i = o+1;i<MLBTeamVector.size();i++) {
                        if(MLBTeamVector[i].getLeague() == "American"){
                            int c = MLBTeamVector[i].getTeamName()[0].toUpper().unicode();
                            bool spotF = false;
                            int k = 0;
                            while (!spotF && k < vec.size()) {
                                if(c < MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (c == MLBTeamVector[vec[k]].getTeamName()[0].toUpper().unicode()) {
                                    int j = 1;
                                    while (!spotF && j < MLBTeamVector[i].getTeamName().size()&& j < MLBTeamVector[vec[k]].getTeamName().size()) {
                                        if(MLBTeamVector[i].getTeamName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if (MLBTeamVector[i].getTeamName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getTeamName()[j].toUpper().unicode())
                                            j++;
                                        else {
                                            if(k+1 == vec.size()){
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else if (MLBTeamVector[k+1].getTeamName()[0].toUpper().unicode() != MLBTeamVector[i].getTeamName()[0].toUpper().unicode()) {
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else {
                                                k++;
                                            }
                                        }
                                    }
                                    if(!spotF){
                                        if(MLBTeamVector[i].getTeamName().size() < MLBTeamVector[vec[k]].getTeamName().size()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if(MLBTeamVector[i].getTeamName().size() > MLBTeamVector[vec[k]].getTeamName().size()){
                                            vec.insert(k+1,i);
                                            spotF = true;
                                        }
                                    }
                                }
                                else {
                                    k++;
                                }
                            }
                            if(!spotF){
                                vec.insert(k,i);
                                spotF = true;
                            }
                        }
                    }
                }
            }
            updateTable(vec);
        break;
    case 2: if(leagueSetting == 0){
                vec.push_back(0);
                for (int i = 1;i<MLBTeamVector.size();i++) {
                    int c = MLBTeamVector[i].getStadiumName()[0].toUpper().unicode();
                    bool spotF = false;
                    int k = 0;
                    while (!spotF && k < vec.size()) {
                        if(c < MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()){
                            vec.insert(k,i);
                            spotF = true;
                        }
                        else if (c == MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()) {
                            int j = 1;
                            while (!spotF && j < MLBTeamVector[i].getStadiumName().size()&& j < MLBTeamVector[vec[k]].getStadiumName().size()) {
                                if(MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode())
                                    j++;
                                else {
                                    if(k+1 == vec.size()){
                                        vec.insert(k+1,i);
                                        spotF = true;
                                    }
                                    else if (MLBTeamVector[k+1].getStadiumName()[0].toUpper().unicode() != MLBTeamVector[i].getStadiumName()[0].toUpper().unicode()) {
                                        vec.insert(k+1,i);
                                        spotF = true;
                                    }
                                    else {
                                        k++;
                                    }
                                }
                            }
                            if(!spotF){
                                if(MLBTeamVector[i].getStadiumName().size() < MLBTeamVector[vec[k]].getStadiumName().size()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if(MLBTeamVector[i].getStadiumName().size() > MLBTeamVector[vec[k]].getStadiumName().size()){
                                    vec.insert(k+1,i);
                                    spotF = true;
                                }
                            }
                        }
                        else {
                            k++;
                        }
                    }
                    if(!spotF){
                        vec.insert(k,i);
                        spotF = true;
                    }
                }
            }
            else if (leagueSetting == 1) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "National" && o <MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                    for (int i = o+1;i<MLBTeamVector.size();i++) {
                        if(MLBTeamVector[i].getLeague() == "National"){
                            int c = MLBTeamVector[i].getStadiumName()[0].toUpper().unicode();
                            bool spotF = false;
                            int k = 0;
                            while (!spotF && k < vec.size()) {
                                if(c < MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (c == MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()) {
                                    int j = 1;
                                    while (!spotF && j < MLBTeamVector[i].getStadiumName().size()&& j < MLBTeamVector[vec[k]].getStadiumName().size()) {
                                        if(MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if (MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode())
                                            j++;
                                        else {
                                            if(k+1 == vec.size()){
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else if (MLBTeamVector[k+1].getStadiumName()[0].toUpper().unicode() != MLBTeamVector[i].getStadiumName()[0].toUpper().unicode()) {
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else {
                                                k++;
                                            }
                                        }
                                    }
                                    if(!spotF){
                                        if(MLBTeamVector[i].getStadiumName().size() < MLBTeamVector[vec[k]].getStadiumName().size()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if(MLBTeamVector[i].getStadiumName().size() > MLBTeamVector[vec[k]].getStadiumName().size()){
                                            vec.insert(k+1,i);
                                            spotF = true;
                                        }
                                    }
                                }
                                else {
                                    k++;
                                }
                            }
                            if(!spotF){
                                vec.insert(k,i);
                                spotF = true;
                            }
                        }
                    }
                }
            }
            else if (leagueSetting == 2) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "American" && o <MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                    for (int i = o+1;i<MLBTeamVector.size();i++) {
                        if(MLBTeamVector[i].getLeague() == "American"){
                            int c = MLBTeamVector[i].getStadiumName()[0].toUpper().unicode();
                            bool spotF = false;
                            int k = 0;
                            while (!spotF && k < vec.size()) {
                                if(c < MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()){
                                    vec.insert(k,i);
                                    spotF = true;
                                }
                                else if (c == MLBTeamVector[vec[k]].getStadiumName()[0].toUpper().unicode()) {
                                    int j = 1;
                                    while (!spotF && j < MLBTeamVector[i].getStadiumName().size()&& j < MLBTeamVector[vec[k]].getStadiumName().size()) {
                                        if(MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() < MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if (MLBTeamVector[i].getStadiumName()[j].toUpper().unicode() == MLBTeamVector[vec[k]].getStadiumName()[j].toUpper().unicode())
                                            j++;
                                        else {
                                            if(k+1 == vec.size()){
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else if (MLBTeamVector[k+1].getStadiumName()[0].toUpper().unicode() != MLBTeamVector[i].getStadiumName()[0].toUpper().unicode()) {
                                                vec.insert(k+1,i);
                                                spotF = true;
                                            }
                                            else {
                                                k++;
                                            }
                                        }
                                    }
                                    if(!spotF){
                                        if(MLBTeamVector[i].getStadiumName().size() < MLBTeamVector[vec[k]].getStadiumName().size()){
                                            vec.insert(k,i);
                                            spotF = true;
                                        }
                                        else if(MLBTeamVector[i].getStadiumName().size() > MLBTeamVector[vec[k]].getStadiumName().size()){
                                            vec.insert(k+1,i);
                                            spotF = true;
                                        }
                                    }
                                }
                                else {
                                    k++;
                                }
                            }
                            if(!spotF){
                                vec.insert(k,i);
                                spotF = true;
                            }
                        }
                    }
                }
            }
            updateTable(vec);
        break;
    case 3: if(leagueSetting == 0){
                vec.push_back(0);
                for (int i = 1;i<MLBTeamVector.size();i++) {
                    bool spotF = false;
                    int k = 0;
                    while (!spotF && k < vec.size()) {
                        if(MLBTeamVector[i].getCapacity() <= MLBTeamVector[vec[k]].getCapacity()){
                            vec.insert(k,i);
                            spotF = true;
                        }
                        else {
                            k++;
                        }
                    }
                    if(!spotF){
                        vec.insert(k,i);
                        spotF = true;
                    }
                }
            }
            else if (leagueSetting ==1) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "National" && o < MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                }
                for (int i = o+1;i<MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "National"){
                        bool spotF = false;
                        int k = 0;
                        while (!spotF && k < vec.size()) {
                            if(MLBTeamVector[i].getCapacity() <= MLBTeamVector[vec[k]].getCapacity()){
                                vec.insert(k,i);
                                spotF = true;
                            }
                            else {
                                k++;
                            }
                        }
                        if(!spotF){
                            vec.insert(k,i);
                            spotF = true;
                        }
                    }
                }
            }
            else if (leagueSetting ==2) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "American" && o < MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                }
                for (int i = o+1;i<MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "American"){
                        bool spotF = false;
                        int k = 0;
                        while (!spotF && k < vec.size()) {
                            if(MLBTeamVector[i].getCapacity() <= MLBTeamVector[vec[k]].getCapacity()){
                                vec.insert(k,i);
                                spotF = true;
                            }
                            else {
                                k++;
                            }
                        }
                        if(!spotF){
                            vec.insert(k,i);
                            spotF = true;
                        }
                    }
                }
            }
            updateTable(vec);
        break;
    case 4: if(leagueSetting == 0){
                vec.push_back(0);
                for (int i = 1;i<MLBTeamVector.size();i++) {
                    bool spotF = false;
                    int k = 0;
                    while (!spotF && k < vec.size()) {
                        if(MLBTeamVector[i].getDateOpened() <= MLBTeamVector[vec[k]].getDateOpened()){
                            vec.insert(k,i);
                            spotF = true;
                        }
                        else {
                            k++;
                        }
                    }
                    if(!spotF){
                        vec.insert(k,i);
                        spotF = true;
                    }
                }
            }
            else if (leagueSetting == 1) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "National" && o < MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                }
                for (int i = o+1;i<MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "National"){
                        bool spotF = false;
                        int k = 0;
                        while (!spotF && k < vec.size()) {
                            if(MLBTeamVector[i].getDateOpened() <= MLBTeamVector[vec[k]].getDateOpened()){
                                vec.insert(k,i);
                                spotF = true;
                            }
                            else {
                                k++;
                            }
                        }
                        if(!spotF){
                            vec.insert(k,i);
                            spotF = true;
                        }
                    }
                }
            }
            else if (leagueSetting == 2) {
                int o = 0;
                while (MLBTeamVector[o].getLeague() != "American" && o < MLBTeamVector.size()) {
                    o++;
                }
                if(o < MLBTeamVector.size()){
                    vec.push_back(o);
                }
                for (int i = o+1;i<MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "American"){
                        bool spotF = false;
                        int k = 0;
                        while (!spotF && k < vec.size()) {
                            if(MLBTeamVector[i].getDateOpened() <= MLBTeamVector[vec[k]].getDateOpened()){
                                vec.insert(k,i);
                                spotF = true;
                            }
                            else {
                                k++;
                            }
                        }
                        if(!spotF){
                            vec.insert(k,i);
                            spotF = true;
                        }
                    }
                }
            }
            updateTable(vec);
        break;
    case 5: if(leagueSetting == 0){
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(impNum < MLBTeamVector[i].getCenterField()){
                        impNum = MLBTeamVector[i].getCenterField();
                        vec.clear();
                        vec.push_back(i);
                    }
                    else if (impNum == MLBTeamVector[i].getCenterField()) {
                        vec.push_back(i);
                    }
                }
            }
            else if (leagueSetting ==1) {
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() =="National"){
                        if(impNum < MLBTeamVector[i].getCenterField()){
                            impNum = MLBTeamVector[i].getCenterField();
                            vec.clear();
                            vec.push_back(i);
                        }
                        else if (impNum == MLBTeamVector[i].getCenterField()) {
                            vec.push_back(i);
                        }
                    }
                }
            }
            else if (leagueSetting ==2) {
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() =="American"){
                        if(impNum < MLBTeamVector[i].getCenterField()){
                            impNum = MLBTeamVector[i].getCenterField();
                            vec.clear();
                            vec.push_back(i);
                        }
                        else if (impNum == MLBTeamVector[i].getCenterField()) {
                            vec.push_back(i);
                        }
                    }
                }
            }
            ui->stadiumNameList_2->clear();
            ui->centerFieldList_2->clear();
            for (int i = 0;i < vec.size();i++) {
                ui->stadiumNameList_2->addItem(MLBTeamVector[vec[i]].getTeamName());
                ui->centerFieldList_2->addItem((QString::number(MLBTeamVector[vec[i]].getCenterField()))+" ("+QString::number(round(MLBTeamVector[vec[i]].getCenterField()*.3048))+"m)");
            }
            ui->centerFieldStacked_2->setCurrentIndex(1);
        break;
    case 6: if(leagueSetting == 0){
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(impNum > MLBTeamVector[i].getCenterField()){
                        impNum = MLBTeamVector[i].getCenterField();
                        vec.clear();
                        vec.push_back(i);
                    }
                    else if (impNum == MLBTeamVector[i].getCenterField()) {
                        vec.push_back(i);
                    }
                }
            }
            else if (leagueSetting == 1) {
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "National"){
                        if(impNum > MLBTeamVector[i].getCenterField()){
                            impNum = MLBTeamVector[i].getCenterField();
                            vec.clear();
                            vec.push_back(i);
                        }
                        else if (impNum == MLBTeamVector[i].getCenterField()) {
                            vec.push_back(i);
                        }
                    }
                }
            }
            else if (leagueSetting == 2) {
                for (int i = 1;i < MLBTeamVector.size();i++) {
                    if(MLBTeamVector[i].getLeague() == "American"){
                        if(impNum > MLBTeamVector[i].getCenterField()){
                            impNum = MLBTeamVector[i].getCenterField();
                            vec.clear();
                            vec.push_back(i);
                        }
                        else if (impNum == MLBTeamVector[i].getCenterField()) {
                            vec.push_back(i);
                        }
                    }
                }
            }
            ui->stadiumNameList_2->clear();
            ui->centerFieldList_2->clear();
            for (int i = 0;i < vec.size();i++) {
                ui->stadiumNameList_2->addItem(MLBTeamVector[vec[i]].getTeamName());
                ui->centerFieldList_2->addItem((QString::number(MLBTeamVector[vec[i]].getCenterField()))+" ("+QString::number(round(MLBTeamVector[vec[i]].getCenterField()*.3048))+"m)");
            }
            ui->centerFieldStacked_2->setCurrentIndex(1);
        break;
    case 7: for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Retro Modern"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Retro Modern"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Retro Modern"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Retro Classic"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Retro Classic"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Retro Classic"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Modern"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Modern"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Modern"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Contemporary"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Contemporary"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Contemporary"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Jewel Box"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Jewel Box"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Jewel Box"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            for (int i = 0;i<MLBTeamVector.size();i++) {
                if(leagueSetting == 0){
                    QString qs = MLBTeamVector[i].getTypelogy();
                    if(qs == "Multipurpose"){
                        vec.push_front(i);
                    }
                }
                else if (leagueSetting == 1) {
                    if(MLBTeamVector[i].getLeague()=="National"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Multipurpose"){
                            vec.push_front(i);
                        }
                    }
                }
                else if (leagueSetting == 2) {
                    if(MLBTeamVector[i].getLeague()=="American"){
                        QString qs = MLBTeamVector[i].getTypelogy();
                        if(qs == "Multipurpose"){
                            vec.push_front(i);
                        }
                    }
                }
            }
            updateTable(vec);
        break;
    }
}

void MainWindow::on_addTeamsButton_clicked(){
    if(filesAdded == -1){
        readMLBFile2("C:\\Users\\water\\Documents\\GitHub\\ST6R-MLB\\mlb\\data2.txt");
        filesAdded++;
    }
}

void MainWindow::on_deleteTeamButton_clicked(){
    if(ui->manageTable->currentRow()<MLBTeamVector.size()&&ui->manageTable->currentRow()>=0){
        int k = 0;
        bool found = false;

        while(!found && k < MLBTeamVector.size()){
            if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
                found = true;
            else
                ++k;
        }
        int i = ui->manageTable->currentRow();
        if(found)
            MLBTeamVector.remove(k);
        ui->manageTable->removeRow(i);
        ui->priceList_2->clear();
        ui->souvenirList_2->clear();
    }
}

void MainWindow::on_manageTeamsBackButton_clicked(){
    ui->bbFanStackedWidget->setCurrentIndex(3);
}

void MainWindow::on_addItemButton_clicked(){
    if(ui->addItemWidget->currentIndex() == 0)
        ui->addItemWidget->setCurrentIndex(1);
    else {
        ui->addItemWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_deleteItemButton_clicked(){
    //deletes the item selected on the manageMenuListWidget (not the price widget)
    if(ui->souvenirList_2->currentItem() != nullptr)
    {
        //perform search for the item to be removed
        int k = 0;
        bool found = false;

        while(!found && k < MLBTeamVector.size())
        {
            if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
            {
                //QTextStream(stdout) << ui->manageRestaurantListWidget->currentItem()->text() << endl;
                found = true;
            }
            else
            {
                ++k;
            }
        }
        if(found){
            //remove items from lists
            int index = ui->souvenirList_2->currentRow();
            ui->souvenirList_2->takeItem(index);
            ui->priceList_2->takeItem(index);

            //remove items from data structure
            MLBTeamVector[k].removeMenuItem(index);
        }
    }
}

void MainWindow::on_souvenirList_2_itemDoubleClicked(QListWidgetItem *item)
{
    //allow editing of the item name if double clicked
    ui->souvenirList_2->openPersistentEditor(item);
}

void MainWindow::on_priceList_2_itemDoubleClicked(QListWidgetItem *item)
{
    //allow editing of the item price if double clicked
    ui->priceList_2->openPersistentEditor(item);
}

void MainWindow::on_souvenirList_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(ui->souvenirList_2->isPersistentEditorOpen(previous))
    {
        int k = 0;
        bool found = false;

        while(!found && k < MLBTeamVector.size())
        {
            if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
                found = true;
            else
                k++;
        }
        if(found)
            MLBTeamVector[k].changeSouvenirName(previous->listWidget()->row(previous),previous->text());
    }
    ui->souvenirList_2->closePersistentEditor(previous);
    ui->priceList_2->setCurrentRow(current->listWidget()->currentRow());
}

void MainWindow::on_priceList_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(ui->priceList_2->isPersistentEditorOpen(previous))
    {
        int k = 0;
        bool found = false;

        while(!found && k < MLBTeamVector.size())
        {
            if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
                found = true;
            else
                k++;
        }
        if(found){
            if(isFloatNumber(previous->text()))
            {
                MLBTeamVector[k].changeSouvenirPrice(previous->listWidget()->row(previous),previous->text().toDouble());
            }
            else
            {
                //input is not a float
                QMessageBox::warning(nullptr, "Error", "Invalid Price Input! Please Enter a Float");
                previous->setText(QString::number(MLBTeamVector[k].getSouvenirPrice(previous->listWidget()->row(previous))));

            }
        }
        ui->priceList_2->closePersistentEditor(previous);
    }
    ui->souvenirList->setCurrentRow(current->listWidget()->currentRow());
}

void MainWindow::on_addItemConfirmationBox_accepted(){
    if(ui->itemNameEntry->text() != "" && ui->itemPriceEntry->text() != "")
    {
        //check for valid float
        if(isFloatNumber(ui->itemPriceEntry->text())){
            int k = 0;
            bool found = false;
            while(!found && k < MLBTeamVector.size()){
                if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
                    found = true;
                else
                    k++;
            }
            //perform search for the item
            if(found){
                MLBTeamVector[k].addMenuItem(ui->itemNameEntry->text(), (double(int((ui->itemPriceEntry->text().toDouble()) * 100)))/100 );
                ui->souvenirList_2->addItem(MLBTeamVector[k].getSouvenirName(MLBTeamVector[k].getMenuSize()-1));
                ui->priceList_2->addItem(QString::number(MLBTeamVector[k].getSouvenirPrice(MLBTeamVector[k].getMenuSize()-1)));
            }
        }
        else
            QMessageBox::warning(nullptr, "Error", "Invalid Price Input! Please Enter a Float");
    }

    //clear line edits once finished with them
    ui->itemNameEntry->clear();
    ui->itemPriceEntry->clear();

    //hide the add item overlay
    ui->addItemWidget->setCurrentIndex(0);
}

void MainWindow::on_manageTable_itemDoubleClicked(QTableWidgetItem *item)
{
    //if a restaurant name is double clicked, it allows user to edit the name directly
    ui->manageTable->openPersistentEditor(item);
}

void MainWindow::on_manageTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous){
    if(ui->souvenirList_2->isPersistentEditorOpen(ui->souvenirList_2->currentItem())){
        ui->souvenirList_2->closePersistentEditor(ui->souvenirList_2->currentItem());
        MLBTeamVector[previous->tableWidget()->row(previous)].changeSouvenirName(ui->manageTable->currentRow(),ui->manageTable->currentItem()->text());
    }
    if(ui->priceList_2->isPersistentEditorOpen(ui->priceList_2->currentItem())){
        ui->priceList_2->closePersistentEditor(ui->priceList_2->currentItem());
        MLBTeamVector[previous->tableWidget()->row(previous)].changeSouvenirPrice(ui->priceList_2->currentRow(),ui->priceList_2->currentItem()->text().toDouble());
    }

    if(ui->manageTable->isPersistentEditorOpen(previous)){
        ui->manageTable->closePersistentEditor(previous);
        switch(previous->column()){
        case 0: MLBTeamVector[previous->tableWidget()->row(previous)].changeteamName(previous->text());
            break;
        case 1: MLBTeamVector[previous->tableWidget()->row(previous)].changeStadiumName(previous->text());
            break;
        case 2: if(isIntNumber(previous->text()))
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeCapacity(previous->text().toInt());
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid number Input! Please Enter a valid int");
                ui->manageTable->setItem(previous->row(),2,new QTableWidgetItem((QString::number(MLBTeamVector[previous->row()].getCapacity()))));
            break;
        case 3: MLBTeamVector[previous->tableWidget()->row(previous)].changeLocation(previous->text());
            break;
        case 4: if(previous->text()[0].toUpper() == "G")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeSurface("Grass");
                else if(previous->text()[0].toUpper() == "A")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeSurface("AstroTurf GameDay Grass");
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid Input, Grass or AstroTurf");
                ui->manageTable->setItem(previous->row(),4,new QTableWidgetItem(MLBTeamVector[previous->row()].getSurface()));
            break;
        case 5: if(previous->text()[0].toUpper() == "A")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeLeague("American");
                else if(previous->text()[0].toUpper() == "N")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeLeague("National");
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid Input, American or National");
                ui->manageTable->setItem(previous->row(),5,new QTableWidgetItem(MLBTeamVector[previous->row()].getLeague()));
            break;
        case 6: if(isIntNumber(previous->text()))
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeDateOpened(previous->text().toInt());
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid number Input! Please Enter a valid int");
                ui->manageTable->setItem(previous->row(),6,new QTableWidgetItem((QString::number(MLBTeamVector[previous->row()].getDateOpened()))));
            break;
        case 7: if(isIntNumber(previous->text()))
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeCenterField(previous->text().toInt());
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid number Input! Please Enter a valid int");
                ui->manageTable->setItem(previous->row(),7,new QTableWidgetItem((QString::number(MLBTeamVector[previous->row()].getCenterField()))+" ("+QString::number(round(MLBTeamVector[previous->row()].getCenterField()*.3048))+"m)"));
            break;
        case 8: if(previous->text()[0].toUpper() == "C")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeTypelogy("Contemporary");
                else if(previous->text().toUpper() == "RETRO MODERN")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeTypelogy("Retro Modern");
                else if(previous->text().toUpper() == "RETRO CLASSIC")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeTypelogy("Retro Classic");
                else if(previous->text()[0].toUpper() == "M")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeTypelogy("Multipurpose");
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid Input, Contemporary, Retro Modern, Retro Classic, or Multipurpose");
                ui->manageTable->setItem(previous->row(),8,new QTableWidgetItem(MLBTeamVector[previous->row()].getTypelogy()));
            break;
        case 9: if(previous->text()[0].toUpper() == "O")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeRoofType("Open");
                else if(previous->text()[0].toUpper() == "F")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeRoofType("Fixed");
                else if(previous->text()[0].toUpper() == "R")
                    MLBTeamVector[previous->tableWidget()->row(previous)].changeRoofType("Retractable");
                else
                    QMessageBox::warning(nullptr, "Error", "Invalid Input, Open, Fixed, or Retractable");
                ui->manageTable->setItem(previous->row(),9,new QTableWidgetItem(MLBTeamVector[previous->row()].getRoofType()));
            break;
        }
    }

    ui->souvenirList_2->blockSignals(true);
    ui->priceList_2->blockSignals(true);
    ui->souvenirList_2->clear();
    ui->priceList_2->clear();
    ui->souvenirList_2->blockSignals(false);
    ui->priceList_2->blockSignals(false);

    ui->manageTable->setCurrentCell(current->row(),current->column());
    ui->souvenirList_2->clear();
    ui->priceList_2->clear();

    //perform search for the item
    int k = 0;
    bool found = false;
    while(!found && k < MLBTeamVector.size()){
        if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
            found = true;
        else
            k++;
    }
    if(found){
        for (int j = 0;j<MLBTeamVector[k].getMenuSize();j++) {
            ui->souvenirList_2->addItem(MLBTeamVector[k].getSouvenirName(j));
            ui->priceList_2->addItem(QString::number(MLBTeamVector[k].getSouvenirPrice(j)));
        }
    }
}

void MainWindow::on_addItemConfirmationBox_rejected(){
    ui->itemNameEntry->clear();
    ui->itemPriceEntry->clear();

    ui->addItemWidget->setCurrentIndex(0);
}

//Helpers
void MainWindow::updateTable(QVector<int> vec){
    ui->manageTable->setRowCount(vec.size());
    for(int i = 0; i < vec.size(); i++){
        int t = vec[i];
        ui->manageTable->setItem(i,0,new QTableWidgetItem(MLBTeamVector[t].getTeamName()));
        ui->manageTable->setItem(i,1,new QTableWidgetItem(MLBTeamVector[t].getStadiumName()));
        ui->manageTable->setItem(i,2,new QTableWidgetItem((QString::number(MLBTeamVector[t].getCapacity()))));
        ui->manageTable->setItem(i,3,new QTableWidgetItem(MLBTeamVector[t].getLocation()));
        ui->manageTable->setItem(i,4,new QTableWidgetItem(MLBTeamVector[t].getSurface()));
        ui->manageTable->setItem(i,5,new QTableWidgetItem(MLBTeamVector[t].getLeague()));
        ui->manageTable->setItem(i,6,new QTableWidgetItem((QString::number(MLBTeamVector[t].getDateOpened()))));
        ui->manageTable->setItem(i,7,new QTableWidgetItem((QString::number(MLBTeamVector[t].getCenterField()))+" ("+QString::number(round(MLBTeamVector[t].getCenterField()*.3048))+"m)"));
        ui->manageTable->setItem(i,8,new QTableWidgetItem(MLBTeamVector[t].getTypelogy()));
        ui->manageTable->setItem(i,9,new QTableWidgetItem(MLBTeamVector[t].getRoofType()));
    }
}

bool MainWindow::isFloatNumber(const QString& Qstring)
{
    string stdString = Qstring.toStdString();

    string::const_iterator it = stdString.begin();
    bool decimalPoint = false;
    unsigned int minSize = 0;
    if(stdString.size()>0 && (stdString[0] == '-' || stdString[0] == '+')){
      it++;
      minSize++;
    }
    while(it != stdString.end()){
      if(*it == '.'){
        if(!decimalPoint) decimalPoint = true;
        else break;
      }else if(!std::isdigit(*it) && ((*it!='f') || it+1 != stdString.end() || !decimalPoint)){
        break;
      }
      ++it;
    }
    return stdString.size() > minSize && it == stdString.end() && Qstring.toFloat() >=0;
}

bool MainWindow::isIntNumber(const QString& Qstring){
    string stdString = Qstring.toStdString();

    string::const_iterator it = stdString.begin();
    unsigned int minSize = 0;
    if(stdString.size()>0 && (stdString[0] == '-' || stdString[0] == '+')){
      it++;
      minSize++;
    }
    while(it != stdString.end()){
        if(!std::isdigit(*it) && ((*it!='f') || it+1 != stdString.end())){
            break;
      }
      ++it;
    }
    return stdString.size() > minSize && it == stdString.end() && Qstring.toInt() >=0;
}
