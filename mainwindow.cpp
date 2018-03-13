#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>
#include <QFileDialog>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Server=new QTcpServer(this);
    connect(Server,SIGNAL(newConnection()),this,SLOT(ConnectionSendImage()));

            if(!Server->listen(QHostAddress::Any,1234))
            {
                //qDebug() << "Could not start server";
            }
            else
            {
                //qDebug() << "Listening...";
            }

SocketSendImage=NULL;
on_Disconnected();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectionSendImage()
{
    if (SocketSendImage) {
        SocketSendImage->close();
        delete  SocketSendImage;

    }
     SocketSendImage= Server->nextPendingConnection();
     connect(SocketSendImage,SIGNAL(disconnected()),this,SLOT(on_Disconnected()));
     on_Connected();


}

QByteArray MainWindow::formImageHead(QByteArray by){
    int len=by.length();
    int i=0;
    for(i=10-len;i>0;i--){
        by=by.prepend('0');
    }
    return by;
}

void MainWindow::setImage(const QString &fileName)
{

   m_image=QImage(fileName);
   QPixmap Pixmap=QPixmap::fromImage(m_image.scaled(ui->labe_image->size()));
   ui->labe_image->setPixmap(Pixmap);

   if (m_image.isNull()) {
        return;
   }

   // qDebug()<<"setImage  SocketStream";

    if (!SocketSendImage) {
        return;


    }

    long len=0;

    QByteArray by;
    QBuffer buffer(&by);        // Construct a QBuffer object using the QbyteArray
    m_image.save(&buffer,"JPG"); // Save the QImage data into the QBuffer
    len=by.length();
    by.prepend(formImageHead(QByteArray::number((qlonglong)len)));
    len=SocketSendImage->write(by);

    SocketSendImage->flush();

    //    server.close();

}

void MainWindow::on_Connected()
{
  ui->label_posCon->setPixmap(QPixmap(":/images/connected.png"));
//    ui->pushButton_Open->setEabled(true);
}

void MainWindow::on_Disconnected()
{
  ui->label_posCon->setPixmap(QPixmap(":/images/disconnected.png"));
  if (SocketSendImage) {
      SocketSendImage->close();
      delete  SocketSendImage;
      SocketSendImage=NULL;
  }
  //ui->pushButton_Open->setDisabled(true);

}

void MainWindow::on_actionOpen_triggered()
{
    on_pushButton_Open_clicked();
}

void MainWindow::on_pushButton_Open_clicked()
{
 QString fileName= QFileDialog::getOpenFileName(this,"OpenFile Image",QDir::homePath()+"/Pictures","image files (*.JPEG;*.JPG;*.JPE;*.PNG)");
 if (fileName.isEmpty()) {
     return;
 }
   setImage(fileName);


}
