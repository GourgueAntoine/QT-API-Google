#include "httprest.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

HttpRest::HttpRest():
    dataBuffer(new QByteArray)
{

}


HttpRest::~HttpRest()
{

}

void HttpRest::requeteRestGET()
{
    //Requete Google Maps
    QString url_def = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?language=fr&location=43.3807801,1.3069362&radius=&keyword=&key=AIzaSyDGA1LfAItRLRZwgmuk3S6JWBB8JQUVpBw";

        m_mot_clef = "&keyword=" + m_mot_clef;
        url_def.replace("&keyword=", m_mot_clef);
        m_rayon = "&radius=" + m_rayon;
        url_def.replace("&radius=", m_rayon);


    QUrl url = QUrl::fromUserInput(url_def);

    reply = qnam.get(QNetworkRequest(url));//Lancer la requette

                        //Connect pour lecture données reçues
    connect(reply, &QIODevice::readyRead, this, &HttpRest::httpReadyRead);
                        //Connect pour fin de réception données
    connect(reply, &QNetworkReply::finished, this, &HttpRest::httpFinished);
}



void HttpRest::httpReadyRead() //Nouvelles données reçues
{
    dataBuffer->append(reply->readAll());
}

void HttpRest::httpFinished() //fin de réception
{
    //Vide les buffers de réception
    reply->deleteLater();
    //reply->Q_NULLPTR;
}

QNetworkReply* HttpRest::getReply()
{
    return reply;
}

QByteArray* HttpRest::getDataBuffer()
{
    return dataBuffer;
}
