#ifndef TRAY_H
#define TRAY_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QNetworkCookie>

class Tray : public QWidget
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = 0);
    void deelSuccess(QList<QNetworkCookie>);
private:
    QNetworkAccessManager* manager;     //HTTP链接管理
    QSystemTrayIcon* icon;              //最小化托盘
    QString userId;
    //QList<QNetworkCookie> allcookies;

private:
    void deelFinished(QNetworkReply*);
signals:

public slots:
};

#endif // TRAY_H
