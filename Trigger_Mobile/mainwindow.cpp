#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    bool con_status = socket->bind(QHostAddress::Any,30);
    connect(socket,SIGNAL(readyRead()), this, SLOT(receiveMsg()));
    if (con_status){
        cout << "Remote Start Waiting on Port:" << "666" <<endl;
    }else{
        cout << "Fail to open port : " <<  "myport" << endl;
    }
    QSettings settings("CIME", "expStarter");
    ui->lineEdit_ip1->setText(settings.value("ip1").toString());
    ui->lineEdit_ip2->setText(settings.value("ip2").toString());
    ui->lineEdit_ip3->setText(settings.value("ip3").toString());
    ui->lineEdit_ip4->setText(settings.value("ip4").toString());

    ui->lineEdit_port1->setText(settings.value("port1").toString());
    ui->lineEdit_port2->setText(settings.value("port2").toString());
    ui->lineEdit_port3->setText(settings.value("port3").toString());
    ui->lineEdit_port4->setText(settings.value("port4").toString());
}

MainWindow::~MainWindow()
{
    QSettings settings("CIME", "expStarter");
    settings.setValue("ip1",ui->lineEdit_ip1->text());
    settings.setValue("ip2",ui->lineEdit_ip2->text());
    settings.setValue("ip3",ui->lineEdit_ip3->text());
    settings.setValue("ip4",ui->lineEdit_ip4->text());
    settings.setValue("port1",ui->lineEdit_port1->text());
    settings.setValue("port2",ui->lineEdit_port2->text());
    settings.setValue("port3",ui->lineEdit_port3->text());
    settings.setValue("port4",ui->lineEdit_port4->text());
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{
    port1 = ui->lineEdit_port1->text().toUInt();
    port2 = ui->lineEdit_port2->text().toUInt();
    port3 = ui->lineEdit_port3->text().toUInt();
    port4 = ui->lineEdit_port4->text().toUInt();
    ip1.setAddress(ui->lineEdit_ip1->text());
    ip2.setAddress(ui->lineEdit_ip2->text());
    ip3.setAddress(ui->lineEdit_ip3->text());
    ip4.setAddress(ui->lineEdit_ip4->text());
    ui->label_status1->setText("-");
    ui->label_status2->setText("-");
    ui->label_status3->setText("-");
    ui->label_status4->setText("-");
    sendMsg(ip1,port1,"T");
    sendMsg(ip2,port2,"T");
    sendMsg(ip3,port3,"T");
    sendMsg(ip4,port4,"T");
}

void MainWindow::on_pushButton_stop_clicked()
{
    port1 = ui->lineEdit_port1->text().toUInt();
    port2 = ui->lineEdit_port2->text().toUInt();
    port3 = ui->lineEdit_port3->text().toUInt();
    port4 = ui->lineEdit_port4->text().toUInt();
    ip1.setAddress(ui->lineEdit_ip1->text());
    ip2.setAddress(ui->lineEdit_ip2->text());
    ip3.setAddress(ui->lineEdit_ip3->text());
    ip4.setAddress(ui->lineEdit_ip4->text());
    sendMsg(ip1,port1,ui->lineEdit_stop1->text());
    sendMsg(ip2,port2,ui->lineEdit_stop2->text());
    sendMsg(ip3,port3,ui->lineEdit_stop3->text());
    sendMsg(ip4,port4,ui->lineEdit_stop4->text());
}
void MainWindow::sendMsg(QHostAddress ip,quint16 port, QString msg){
    QByteArray datagram;
    datagram.append(msg);
    socket->writeDatagram(datagram,ip,port);
}
void  MainWindow::receiveMsg(){
    QByteArray dt;
    QHostAddress hostadr;
    quint16 port;
    dt.resize(socket->pendingDatagramSize());
    socket->readDatagram(dt.data(),dt.size(),&hostadr,&port);
    cout << dt.data() <<endl;
    char* data = dt.data();

    if (hostadr.toIPv4Address()==ip1.toIPv4Address() && port ==port1){
        if (data[0]=='S'){
            ui->label_status1->setText("Started");
        }
        if (data[0]=='F'){
            ui->label_status1->setText("Stoped");
        }
        if (data[0]=='T'){
            ui->label_status1->setText("Test");
        }
    }
    if (hostadr.toIPv4Address()==ip2.toIPv4Address() && port ==port2){
        if (data[0]=='S'){
            ui->label_status2->setText("Started");
        }
        if (data[0]=='F'){
            ui->label_status2->setText("Stoped");
        }
        if (data[0]=='T'){
            ui->label_status2->setText("Test");
        }
    }
    if (hostadr.toIPv4Address()==ip3.toIPv4Address() && port ==port3){
        if (data[0]=='S'){
            ui->label_status3->setText("Started");
        }
        if (data[0]=='F'){
            ui->label_status3->setText("Stoped");
        }
        if (data[0]=='T'){
            ui->label_status3->setText("Test");
        }
    }
    if (hostadr.toIPv4Address()==ip4.toIPv4Address() && port ==port4){
        if (data[0]=='S'){
            ui->label_status4->setText("Started");
        }
        if (data[0]=='F'){
            ui->label_status4->setText("Stoped");
        }
        if (data[0]=='T'){
            ui->label_status4->setText("Test");
        }
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    port1 = ui->lineEdit_port1->text().toUInt();
    port2 = ui->lineEdit_port2->text().toUInt();
    port3 = ui->lineEdit_port3->text().toUInt();
    port4 = ui->lineEdit_port4->text().toUInt();
    ip1.setAddress(ui->lineEdit_ip1->text());
    ip2.setAddress(ui->lineEdit_ip2->text());
    ip3.setAddress(ui->lineEdit_ip3->text());
    ip4.setAddress(ui->lineEdit_ip4->text());

    sendMsg(ip1,port1,ui->lineEdit_start1->text());
    sendMsg(ip2,port2,ui->lineEdit_start2->text());
    sendMsg(ip3,port3,ui->lineEdit_start3->text());
    sendMsg(ip4,port4,ui->lineEdit_start4->text());
}
