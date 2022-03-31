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
    this->resize(this->size());

    GetMainPageRequest request;
    this->api->request(&request, [&](QJsonObject body) {

        QJsonValue backgroundUrl = body.take("background");
        qDebug() << backgroundUrl.toString();

        RawGetRequest request(backgroundUrl.toString());

        this->external->request(&request, [&](QByteArray body) {

            QImage background = QImage::fromData(body);

            /*
            // TODO: add cache
            if (!background.save("bg.jpg"))
            {
                qDebug() << "fail for write file";
                return;
            }*/

            this->backgroundImage = QPixmap::fromImage(background);
            this->ui->backGroundLabel->setPixmap(this->backgroundImage.scaled(this->size().width(), this->size().height()));
            this->ui->backGroundLabel->show();

            this->resize(this->size());

            qDebug() << "ok";
        }, [](QString error) {
            qDebug() << error;
        });

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
