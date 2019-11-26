#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    qDebug() << "hello Misaki";
    manager = new QNetworkAccessManager(this);
    icon = new QSystemTrayIcon(this);
    hide();
    //show();
}

void Tray::deelSuccess(QList<QNetworkCookie> allcookies)
{
    qDebug() << "hello Mis";

    QNetworkRequest request;
    QVariant var;
    var.setValue(allcookies);
    request.setHeader(QNetworkRequest::CookieHeader,var);
    request.setUrl(QUrl("http://yiban.sust.edu.cn/index.php/home/loginqr/userinfo"));

    manager->get(request);
    connect(manager, &QNetworkAccessManager::finished, this, &deelFinished);

}

void Tray::deelFinished(QNetworkReply* reply)
{
    //获取状态码
//    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if(statusCode.isValid())
//        qDebug() << "status code=" << statusCode.toInt();
//    //获取描述信息
//    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//    if(reason.isValid())
//        qDebug() << "reason=" << reason.toString();
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "Failed: " << reply->errorString();
    }
    else
    {
        userId = reply->readAll();
        qDebug() << userId;
        reply->close();
        reply->deleteLater();
    }
}
