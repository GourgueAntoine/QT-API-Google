#ifndef HTTPREST_H
#define HTTPREST_H

#include <QMainWindow>
#include <QObject>
#include <QtNetwork>


class HttpRest : public QObject
{
    Q_OBJECT

private slots :
    void httpFinished();
    void httpReadyRead();

public:
    HttpRest();
    ~HttpRest();
    void requeteRestGET();
    QNetworkReply* getReply();
    QByteArray* getDataBuffer();
    QString m_mot_clef;
    QString m_rayon;

private :
    QNetworkAccessManager qnam;
    QNetworkReply* reply;
    QByteArray* dataBuffer;
};

#endif // HTTPREST_H
