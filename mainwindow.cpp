#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      httpRest(new HttpRest),
      modele(new QStandardItemModel)
{
    ui->setupUi(this);

    //Connection du curseur à sa libération
    //Lorsque le curseur est libéré
    QObject::connect (this->ui->horizontalSlider,
                      SIGNAL(sliderReleased()),
                      this,
                      SLOT(on_getButton_clicked()));

   /* QObject::connect (this->ui->pushButton,
                      SIGNAL(clicked()),
                      this,
                      SLOT(on_getButton_clicked()));

*/

    setWindowTitle(tr("HTTP"));
    ui->tableView->setModel(modele);
}

void MainWindow::on_getButton_clicked() // click slot
{
                    //Récupération du mot clef et rayon
httpRest->m_mot_clef = ui->textEdit->toPlainText();
httpRest->m_rayon = QString::number(this->ui->horizontalSlider->value()*1000);


    httpRest->requeteRestGET();  //Requete REST

                    //Connect pour fin réception données
    connect(httpRest->getReply(), &QNetworkReply::finished,
            this, &MainWindow::restFinishedGET);
}


void MainWindow::restFinishedGET()  // fin de réception
{
    QByteArray*dataBuffer=nullptr;
    dataBuffer = httpRest->getDataBuffer();

    //transformer le databuffer en JsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(*dataBuffer);

    //Extraire le JsonObject que contient le JsonDocument
    QJsonObject jsonObj = doc.object();

    //Extraire le tableau depuis l'object, grâce à son nom: results
    QJsonArray resultatsTab = jsonObj["results"].toArray();

    //dimensionner le modele à la taille du result
    modele->setRowCount(resultatsTab.count());
    modele->setColumnCount(2);

    for(int i = 0; i < resultatsTab.count(); i++) //boucle sur tableau
    {
        //Extraire l'object contenu dans chaque case du tableau
        //QJsonObject resultats = resultatsTab.at(i).toObject();
        QJsonObject resultats = resultatsTab[i].toObject();

        //Extraire les valeurs de name et vicinity
        modele->setItem(i,0,
                        new QStandardItem(resultats["name"].toString()));

        modele->setItem(i,1,
                         new QStandardItem(resultats["vicinity"].toString()));
    }
    dataBuffer->clear();
}

void MainWindow::Get2Rayon(double rayon)
{
    m_rayon     = rayon;

}

void MainWindow::Get2Rayon()
{
    Get2Rayon(this->ui->horizontalSlider->value());

}

void MainWindow::MajChamps()
{
    this->ui->lcdNumber->display(m_rayon);
    this->ui->horizontalSlider->setValue(m_rayon);

}

MainWindow::~MainWindow()
{
    delete ui;
}

