#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "http/Requests.h"
#include "http/ResponseProcessors.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->api = new ApiRequestor(this);
    this->external = new ExternalRequestor(this);

    QFile file("res/style.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());

    GetMainPageRequest request;
    this->api->request(&request, [&](QJsonObject body) {

        QJsonValue backgroundUrl = body.take("background");
        qDebug() << backgroundUrl.toString();

        RawGetRequest request(backgroundUrl.toString());

        this->external->request(&request, [&](QByteArray body) {

            QImage background = QImage::fromData(body);

            this->backgroundImage = QPixmap::fromImage(background);

            this->resizeEvent(new QResizeEvent(this->size(), this->size()));
        }, [](QString error) {
            qDebug() << error;
        });

        QJsonArray socialNetworks = body["socialNetworks"].toArray();

        for (QJsonArray::iterator it = socialNetworks.begin(); it != socialNetworks.end(); it++)
        {
            QString link = it->toObject()["link"].toString();
            QString imgUrl = it->toObject()["imgUrl"].toString();

            RawGetRequest networkIconRequest(imgUrl);
            this->external->request(&networkIconRequest, [&](QByteArray body) {

                QImage img = QImage::fromData(body);

                QLabel *element = new QLabel(this);
                //element.setText(link);

                element->setPixmap(QPixmap::fromImage(img));
                element->setGeometry(0, 0, 40, 40);

                this->ui->socialNetworkLayout->addWidget(element);

            }, [](QString error) {
                qDebug() << error;
            });


        }
    }, [](QString error) {
        qDebug() << error;
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int w = event->size().width(),
        h = event->size().height();

    this->ui->backGroundLabel->setGeometry(0, 0, w, h);
    this->ui->backGroundLabel->setPixmap(this->backgroundImage.scaled(w, h));
    this->ui->backGroundLabel->show();
}
