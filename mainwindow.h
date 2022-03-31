#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmovie.h"
#include "QResizeEvent"
#include "QShowEvent"

#include "http/Requestors.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ApiRequestor *api;
    ExternalRequestor *external;

    QPixmap backgroundImage;


private slots:
    void resizeEvent(QResizeEvent *event);

};
#endif // MAINWINDOW_H
