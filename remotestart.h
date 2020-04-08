#ifndef REMOTESTART_H
#define REMOTESTART_H

#include <QObject>
#include <QUdpSocket>
class remoteStart : public QObject
{
    Q_OBJECT
public:
    remoteStart(quint16 myport);
    ~remoteStart();
    void SendMsg(QHostAddress ip,quint16 port, QString msg);

private:
    QUdpSocket *socket_remoteStart;

signals:
    void signalStart();
    void signalStop();
public slots:
    void ReceiveMsg();
};

#endif // REMOTESTART_H
