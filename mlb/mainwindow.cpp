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
    listTwo = -1;

    readMLBFile("C:\\Users\\water\\Documents\\GitHub\\ST6R-MLB\\mlb\\data.txt");

    //Set Stacked Widgets
    ui->primaryStackedWidget->setCurrentIndex(0);
    ui->loginStackedWidget->setCurrentIndex(0);
    ui->bbFanStackedWidget->setCurrentIndex(0);
    ui->loginInputStackedWidget->setCurrentIndex(0);
    ui->addItemWidget->setCurrentIndex(0);

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
        qDebug() << i;
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
        //remove items from lists
        int index = ui->souvenirList_2->currentRow();
        ui->souvenirList_2->takeItem(index);
        ui->priceList_2->takeItem(index);

        //remove items from data structure
        MLBTeamVector[k].removeMenuItem(index);
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
        ui->priceList_2->closePersistentEditor(previous);
    }
    ui->souvenirList->setCurrentRow(current->listWidget()->currentRow());
}

void MainWindow::on_addItemConfirmationBox_accepted(){
    if(ui->itemNameEntry->text() != "" && ui->itemPriceEntry->text() != "")
    {
        //check for valid float
        if(isFloatNumber(ui->itemPriceEntry->text()))
        {
            //perform search for the item
            MLBTeamVector[listTwo].addMenuItem(ui->itemNameEntry->text(), (double(int((ui->itemPriceEntry->text().toDouble()) * 100)))/100 );
            ui->souvenirList_2->addItem(MLBTeamVector[listTwo].getSouvenirName(MLBTeamVector[listTwo].getMenuSize()-1));
            ui->priceList_2->addItem(QString::number(MLBTeamVector[listTwo].getSouvenirPrice(MLBTeamVector[listTwo].getMenuSize()-1)));
        }
        else
        {
            QMessageBox::warning(nullptr, "Error", "Invalid Price Input! Please Enter a Float");
        }
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
    //solve bug where program is crashign when changing row on restaurant list widget
    //close persistent editor and update vector with whatever is edited
    if(ui->souvenirList_2->isPersistentEditorOpen(ui->souvenirList_2->currentItem()))
    {
        ui->souvenirList_2->closePersistentEditor(ui->souvenirList_2->currentItem());
        MLBTeamVector[previous->tableWidget()->row(previous)].changeSouvenirName(ui->manageTable->currentRow(),ui->manageTable->currentItem()->text());
    }
    //solve bug where program is crashign when changing row on restaurant list widget
    //close persistent editor and update vector with whatever is edited
    if(ui->priceList_2->isPersistentEditorOpen(ui->priceList_2->currentItem()))
    {
        ui->priceList_2->closePersistentEditor(ui->priceList_2->currentItem());
        MLBTeamVector[previous->tableWidget()->row(previous)].changeSouvenirPrice(ui->priceList_2->currentRow(),ui->priceList_2->currentItem()->text().toDouble());
    }


    if(ui->manageTable->isPersistentEditorOpen(previous))
    {
        //close any editors and update the vector with the new name of restaurant
        ui->manageTable->closePersistentEditor(previous);
        MLBTeamVector[previous->tableWidget()->row(previous)].changeteamName(previous->text());
    }

    //update the menu list when a new restaurant is selected
    ui->souvenirList_2->blockSignals(true);
    ui->priceList_2->blockSignals(true);
    ui->souvenirList_2->clear();
    ui->priceList_2->clear();
    ui->souvenirList_2->blockSignals(false);
    ui->priceList_2->blockSignals(false);

    qDebug() << MLBTeamVector[1].getTeamName();

    ui->manageTable->setCurrentCell(current->row(),current->column());
    ui->souvenirList_2->clear();
    ui->priceList_2->clear();
    const QPoint loc(ui->manageTable->currentRow(),0);

    qDebug() << MLBTeamVector[0].getSouvenirName(1);

    //perform search for the item
    int k = 0;
    bool found = false;

    while(!found && k < MLBTeamVector.size()){
        if(ui->manageTable->item(ui->manageTable->currentRow(),0)->text() == MLBTeamVector[k].getTeamName())
            found = true;
        else
            k++;
    }
    for (int j = 0;j<MLBTeamVector[k].getMenuSize();j++) {
        ui->souvenirList_2->addItem(MLBTeamVector[k].getSouvenirName(j));
        ui->priceList_2->addItem(QString::number(MLBTeamVector[k].getSouvenirPrice(j)));
    }
    listTwo = k;
}

void MainWindow::on_addItemConfirmationBox_rejected(){
    ui->itemNameEntry->clear();
    ui->itemPriceEntry->clear();

    ui->addItemWidget->setCurrentIndex(0);
}

//Helpers
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
