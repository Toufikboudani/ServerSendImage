#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}
class QTcpServer;
class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    QByteArray formImageHead(QByteArray by);
public slots:
    void setImage(const QString &fileName);
private slots:

    void on_Connected();

    void on_Disconnected();

    void ConnectionSendImage();

    void on_actionOpen_triggered();

    void on_pushButton_Open_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *Server;
    QTcpSocket *SocketSendImage;
    QImage m_image;
};

#endif // MAINWINDOW_H
