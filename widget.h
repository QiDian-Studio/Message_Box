#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include <QThread>
#include <QDebug>
#include "logintest.h"

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
    void ReplyFinished();

    //处理窗口关闭槽函数，关闭线程，防止资源泄露
    void DeelClose();

    void DeelFinish();
private:
    Ui::Widget *ui;
    QNetworkReply* reply;   //HTTP请求返回对象
    QThread* thread;        //线程
    LoginTest* loginTest;   //线程对象

signals:
    void ThreadStart();        //开启进程信号
};

#endif // WIDGET_H
