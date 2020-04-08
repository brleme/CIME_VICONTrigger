#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpVicon = new UDP_vicon();
    QSettings settings("CIME", "ViconTrigger");

    ui->lineEdit_viconIP->setText(settings.value("ViconIP").toString());
    ui->lineEdit_viconPORT->setText(settings.value("ViconPORT").toString());
    ui->lineEdit_name->setText(settings.value("Name").toString());
    ui->lineEdit_description->setText(settings.value("Description").toString());
    ui->lineEdit_databasePath->setText(settings.value("DatabasePath").toString());
    ui->textEdit_notes->setText(settings.value("Notes").toString());
}

MainWindow::~MainWindow(){
    QSettings settings("CIME", "ViconTrigger");
    settings.setValue("ViconIP",ui->lineEdit_viconIP->text());
    settings.setValue("ViconPORT",ui->lineEdit_viconPORT->text());
    settings.setValue("Name",ui->lineEdit_name->text());
    settings.setValue("Description",ui->lineEdit_description->text());
    settings.setValue("DatabasePath",ui->lineEdit_databasePath->text());
    settings.setValue("Notes",ui->textEdit_notes->toPlainText());
    delete ui;
}




void MainWindow::on_pushButton_start_clicked(bool checked){
    if (checked){
        udpVicon->setViconAddress(ui->lineEdit_viconIP->text(),ui->lineEdit_viconPORT->text().toInt());
        udpVicon->setNewSession(ui->lineEdit_name->text(),ui->lineEdit_databasePath->text(),ui->lineEdit_description->text(),ui->textEdit_notes->toPlainText());
        udpVicon->start();
        ui->pushButton_start->setText("Stop");
    }else{
        udpVicon->stop();
        ui->pushButton_start->setText("Start");
    }
}



void MainWindow::slotStart(){
    on_pushButton_start_clicked(true);
    ui->pushButton_start->setChecked(true);
    cout << "remotely ... ";
}
void MainWindow::slotStop(){
    on_pushButton_start_clicked(false);
    ui->pushButton_start->setChecked(false);
    cout << "remotely ...";
}

void MainWindow::on_pushButton_remoteStart_clicked(bool checked){
    if (checked){
        remote = new remoteStart(2525);
        connect(remote,SIGNAL(signalStart()),this,SLOT(slotStart()));
        connect(remote,SIGNAL(signalStop()),this,SLOT(slotStop()));
    }else{
        disconnect(remote,SIGNAL(signalStart()),this,SLOT(slotStart()));
        disconnect(remote,SIGNAL(signalStop()),this,SLOT(slotStop()));
        delete remote;
    }
}
