#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "remotestart.h"
#include "udp_vicon.h"
#include <QSettings>


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
    void on_pushButton_start_clicked(bool checked);
    void slotStart();
    void slotStop();

    void on_pushButton_remoteStart_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    remoteStart *remote;
    UDP_vicon *udpVicon;
};

#endif // MAINWINDOW_H
