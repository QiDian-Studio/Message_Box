#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QEventLoop>
#include "tray.h"
namespace Ui {
class Widget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

    ~MainWidget();

private:
    //登录成功槽函数
    void DeelSuccess();

    //接收获取二维码响应槽函数
    //获取二维码图片并开始监听是否登录成功
    void ReplyFinished1(QNetworkReply*);

    //获取二维码状态
    void ReplyFinished2(QNetworkReply*);

    //处理窗口关闭槽函数，关闭线程，防止资源泄露
    //void DeelClose();

    //void DeelFinish();
private:
    Ui::Widget *ui;
    QNetworkAccessManager* manager;     //连接对象
    //QNetworkReply* reply;             //HTTP请求返回对象
    QString url;                        //二维码url链接
    QString api;                        //二维码状态api
    QList<QNetworkCookie> allcookies;
    QEventLoop* loop;

signals:
    void success(QList<QNetworkCookie>);

};

#endif // WIDGET_H
