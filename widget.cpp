#include "widget.h"
#include "ui_widget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMovie>
#include <QString>
#include <stdlib.h>
#include <time.h>
#include <QMessageBox>
#include <QIcon>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    loop = new QEventLoop(this);


    //初始化图形界面
    ui->setupUi(this);
    //设置界面图标
    setWindowIcon(QIcon("://image/icon.jpg"));
    //设置背景色
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(255, 255, 255)));
    //设置标题
    setWindowTitle("信息监控系统-奇点2019");
    //设置文本框
    ui->labelMessage->setText("请扫码登录");
    //初始化加载页面
    QMovie* movie = new QMovie(this);
    movie->setFileName("://image/wait.gif");
    movie->setScaledSize(QSize(200, 200));
    ui->label->setMovie(movie);

    movie->start();


    //建立连接
    srand(time(nullptr));
    url = "http://yiban.sust.edu.cn/index.php/home/loginqr/makeqr.html";
    url += "?key=";
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳
    QString sDate = QString::number(timeT);
    int num = rand() % 1000;
    QString sRand = QString::number(num);
    url += sDate;
    url += sRand;

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    qDebug() << url;
    //创建一个管理器
    manager = new QNetworkAccessManager(this);
    //发送GET请求
    manager->get(request);

    connect(manager, &QNetworkAccessManager::finished, this, &ReplyFinished1);



}

MainWidget::~MainWidget()
{
    delete ui;
}
void MainWidget::ReplyFinished1(QNetworkReply* reply)
{
    //获取状态码
//    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if(statusCode.isValid())
//        qDebug() << "status code=" << statusCode.toInt();
//    //获取描述信息
//    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//    if(reason.isValid())
//        qDebug() << "reason=" << reason.toString();

    allcookies = manager->cookieJar()->cookiesForUrl(QUrl(url));

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "Failed: " << reply->errorString();
    }
    else
    {
        //接收登录二维码并显示
        QByteArray buffer = reply->readAll();
        QPixmap pic;
        bool ret = pic.loadFromData(buffer, "jpg");
        //qDebug() << "buffer" << buffer;
        qDebug() << ret;
        reply->close();
        reply->deleteLater();
        if(ret)
        {
            ui->label->setPixmap(pic.scaled(250, 250));

            size_t pos = url.indexOf("=");
            QString argv = url.mid(pos + 1);//key=1574706343347
            api="http://yiban.sust.edu.cn/index.php/home/loginqr/status?key=";
            api+=argv;
            qDebug() << "api = " << api;


            QNetworkRequest request;
            QVariant var;
            var.setValue(allcookies);
            request.setHeader(QNetworkRequest::CookieHeader,var);
            request.setUrl(QUrl(api));

            manager->get(request);
            disconnect(manager, &QNetworkAccessManager::finished, this, &ReplyFinished1);
            connect(manager, &QNetworkAccessManager::finished, this, &ReplyFinished2);

        }
        else
        {
            QMessageBox::warning(this, "warning", "出错，请重启程序");
            close();
        }
    }
}

void MainWidget::ReplyFinished2(QNetworkReply* reply)
{
    //获取状态码
//    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if(statusCode.isValid())
//        qDebug() << "status code=" << statusCode.toInt();
//    //获取描述信息
//    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//    if(reason.isValid())
//        qDebug() << "reason=" << reason.toString();

//    QVariant cookie = reply->attribute(QNetworkRequest::CookieSaveControlAttribute).toString();
//    if(cookie.isValid())
//        qDebug() << "cookie=" << cookie.toString();

    allcookies = manager->cookieJar()->cookiesForUrl(QUrl(api));
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "Failed: " << reply->errorString();
    }
    else
    {
        QByteArray buffer = reply->readAll();
//        qDebug() << buffer;
        reply->close();
        reply->deleteLater();
        if(buffer == "101")
        {
//            qDebug() << "Here";
            ui->labelMessage->setText("登录成功！");
            //loop->exit();
            hide();
            emit success(allcookies);
        }
        else
        {
            //QList<QNetworkCookieJar> mycookies;

            QNetworkRequest request;
            QVariant var;
            var.setValue(allcookies);
            request.setHeader(QNetworkRequest::CookieHeader,var);
            request.setUrl(QUrl(api));
            manager->get(request);
        }
    }
}


