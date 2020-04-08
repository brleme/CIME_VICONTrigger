#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <iostream>
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
    void on_pushButton_test_clicked();
    void receiveMsg();
    void on_pushButton_stop_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    void sendMsg(QHostAddress ip,quint16 port, QString msg);
    QHostAddress ip1;
    QHostAddress ip2;
    QHostAddress ip3;
    QHostAddress ip4;
    quint16 port1;
    quint16 port2;
    quint16 port3;
    quint16 port4;

};

#endif // MAINWINDOW_H
