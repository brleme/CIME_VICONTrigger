#include "udp_vicon.h"
using namespace std;
UDP_vicon::UDP_vicon(){
    socket = new QUdpSocket(this);
    //bool con_status = socket->bind(QHostAddress::Any,30);
    //connect(socket,SIGNAL(readyRead()), this, SLOT(receiveMsg()));
    qsrand(QDateTime::currentMSecsSinceEpoch());
    PacketID = qrand();
}
void UDP_vicon::setNewSession(QString Name, QString DatabasePath, QString Description, QString Notes){
    this->Name = Name;
    this->DatabasePath = DatabasePath;
    this->Description = Description;
    this->Notes = Notes;
}
void UDP_vicon::setViconAddress(QString ip, quint16 port){
    vicon_hostadr.setAddress(ip);
    vicon_port = port;
}
void UDP_vicon::start(){
    QByteArray bba;
    xml = new QXmlStreamWriter(&bba);
    xml->writeStartDocument("1.0",false);                       //ok
    xml->writeStartElement("CaptureStart");
    xml->writeStartElement("Name");
    xml->writeAttribute("VALUE",Name);
    xml->writeEndElement();

    xml->writeStartElement("Notes");
    xml->writeAttribute("VALUE",Notes);
    xml->writeEndElement();

    xml->writeStartElement("Description");
    xml->writeAttribute("VALUE",Description);
    xml->writeEndElement();

    xml->writeStartElement("DatabasePath");
    xml->writeAttribute("VALUE",DatabasePath);
    xml->writeEndElement();

    xml->writeStartElement("Delay");
    xml->writeAttribute("VALUE","0");
    xml->writeEndElement();

    xml->writeStartElement("PacketID");
    xml->writeAttribute("VALUE",QString::number(PacketID));
    xml->writeEndElement();
    xml->writeEndElement();
    PacketID++;
    bba.resize(500);
    socket->writeDatagram(bba.data(),bba.size(),vicon_hostadr,vicon_port);
}
void UDP_vicon::stop(){
    QByteArray bba;

    xml = new QXmlStreamWriter(&bba);
    xml->writeStartDocument("1.0",false);                       //ok
    xml->writeStartElement("CaptureStop");

    xml->writeStartElement("Name");
    xml->writeAttribute("VALUE",Name);
    xml->writeEndElement();

    xml->writeStartElement("DatabasePath");
    xml->writeAttribute("VALUE",DatabasePath);
    xml->writeEndElement();

    xml->writeStartElement("Delay");
    xml->writeAttribute("VALUE","0");
    xml->writeEndElement();

    xml->writeStartElement("PacketID");
    xml->writeAttribute("VALUE",QString::number(PacketID));
    xml->writeEndElement();
    xml->writeEndElement();
    PacketID++;
    bba.resize(500);
    socket->writeDatagram(bba.data(),bba.size(),vicon_hostadr,vicon_port);
}
