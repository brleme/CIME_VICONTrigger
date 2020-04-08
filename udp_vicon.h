#ifndef UDP_VICON_H
#define UDP_VICON_H

#include <QObject>
#include <iostream>
#include <QXmlStreamWriter>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDateTime>
#include <QMainWindow>
#include <QString>




class UDP_vicon : public QMainWindow
{
    Q_OBJECT
public:
    UDP_vicon();
    void start();
    void stop();
    void setViconAddress(QString ip, quint16 port);
    void setNewSession(QString Name, QString DatabasePath, QString Description, QString notes);
private:
    QUdpSocket *socket;
    QXmlStreamWriter *xml;
    QByteArray ba;
    int PacketID;
    quint16 vicon_port;
    QHostAddress vicon_hostadr;

    QString Name;
    QString Notes;
    QString Description;
    QString DatabasePath;

};

#endif // UDP_VICON_H
