#include "remotestart.h"
#include <iostream>
using namespace std;
remoteStart::~remoteStart(){
    delete socket_remoteStart;
}
remoteStart::remoteStart(quint16 myport){
//    QHostAddress temp_adr;
//    temp_adr.setAddress("127.0.0.1");
    socket_remoteStart = new QUdpSocket(this);
    bool con_status = socket_remoteStart->bind(QHostAddress::Any, myport);
    connect(socket_remoteStart,SIGNAL(readyRead()), this, SLOT(ReceiveMsg()));
    if (con_status){
        cout << "Remote Start Waiting on Port:" << myport <<endl;
    }else{
        cout << "Fail to open port : " <<  myport << endl;
    }
//    SendMsg(temp_adr,8080, "hello");
}
void  remoteStart::ReceiveMsg(){
    QByteArray dt;
    QHostAddress hostadr;
    quint16 port;
    dt.resize(socket_remoteStart->pendingDatagramSize());
    socket_remoteStart->readDatagram(dt.data(),dt.size(),&hostadr,&port);
    char* data = dt.data();
    if (data[0]=='S'){
        qDebug() << "Signal Start";
        SendMsg(hostadr,port,"S");
        emit signalStart();
    }
    if (data[0]=='F'){
        qDebug() << "Signal Finish";
        SendMsg(hostadr,port,"F");
        emit signalStop();
    }
    if (data[0]=='T'){
        qDebug() << "Communication Test";
        SendMsg(hostadr,port,"T");
    }
}
void remoteStart::SendMsg(QHostAddress ip,quint16 port, QString msg){
    QByteArray datagram;
    datagram.append(msg);
    socket_remoteStart->writeDatagram(datagram,ip,port);
}
