#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qjsonobject.h"
#include <QJsonArray>
#include <QJsonObject>

#include <QJsonDocument>
#include "QObject"
#include <QString>
#include "QtNetwork"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkConfiguration"
#include "QNetworkRequest"
#include <QByteArray>
#include "QtWidgets"
#include "QtScript/QScriptEngine"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSave_clicked()
{
    //Get values from fields
    QString strEmail = ui->txtEmail->text();
    QString strFirstName = ui->txtFirstName->text();
    QString strLastName = ui->txtLastName->text();
    QString strCAN = ui->txtCAN->text();
    QString strHardware = ui->txtHardware->text();
    QString strSerialNo = ui->txtSerialNo->text();

    //Assign values to QVarients
    QVariantMap qVariant;
    qVariant.insert("email", QString(strEmail));
    qVariant.insert("firstname", QString(strFirstName));
    qVariant.insert("lastname", QString(strLastName));
    qVariant.insert("can", QString(strCAN));
    qVariant.insert("hardwareaddress", QString(strHardware));
    qVariant.insert("serialnumber", QString(strSerialNo));

    //convert variants to qjondocument
    const QJsonDocument jsonDocument = QJsonDocument::fromVariant(qVariant);

    //Declare bytearray and assign qjsondocument.
    QByteArray postData;
    postData = jsonDocument.toJson();

    //print json format to string
    QString jsonFormat;
    jsonFormat = jsonDocument.toJson();

    ui->plainTextEdit->appendPlainText(jsonFormat);

    //Connect the site
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("http://dev.onelabspace.com:8080/licenses")));

    QNetworkRequest req;
    req.setUrl(QUrl("http://dev.onelabspace.com:8080/licenses"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager->Accessible;
    //Post the data
    QNetworkReply *reply = manager->post(req,postData);
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));

}

void MainWindow::on_btnClearAll_clicked()
{
    ui->txtCAN->clear();
    ui->txtEmail->clear();
    ui->txtFirstName->clear();
    ui->txtLastName->clear();
    ui->txtHardware->clear();
    ui->txtSerialNo->clear();
    ui->plainTextEdit->clear();
}
