#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

#include "httprest.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    HttpRest*httpRest;
    QStandardItemModel* modele;
    double m_rayon = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void    Get2Rayon(double rayon);
    void    MajChamps();

public slots :
    void Get2Rayon();

private slots:
    void on_getButton_clicked();
    void restFinishedGET();


};
#endif // MAINWINDOW_H
