#include "widget.h"
#include "ui_widget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMovie>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //初始化图形界面
    ui->setupUi(this);
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(255, 255, 255)));
    setWindowTitle("信息监控系统-奇点2019");
    ui->labelMessage->setText("请扫码登录");
    QMovie* movie = new QMovie(this);
    movie->setFileName("://image/wait.gif");
    movie->setScaledSize(QSize(200, 200));
    ui->label->setMovie(movie);
    movie->start();

    //建立连接
    QNetworkRequest request;
    request.setUrl(QUrl("http://yiban.sust.edu.cn/index.php/home/loginqr/makeqr.html?key=1574260172530"));
    //创建一个管理器
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //发送GET请求
    reply = manager->get(request);
    //连接请求结束信号
    //connect(reply, &QNetworkReply::finished(QNetworkReply*), this, &ReplyFinished(QNetworkReply*));
    connect(reply, &QNetworkReply::finished, this, &ReplyFinished);
    //连接响应时返回数据信号
    //connect(reply, QNetworkReply::readyRead, this, &ReplyFinished);

    //初始化线程
    thread = new QThread(this);
    loginTest = new LoginTest;
    loginTest->moveToThread(thread);
    connect(this, &ThreadStart, loginTest, &LoginTest::Test);
    connect(this, &MainWidget::destroyed, this, &DeelClose);
    connect(thread, &QThread::finished, this, &DeelFinish);
    connect(loginTest, &LoginTest::success, this, &DeelSuccess);
}

MainWidget::~MainWidget()
{
    delete ui;
}
void MainWidget::ReplyFinished()
{
    //获取状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();
    //获取描述信息
    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        //接收登录二维码并显示
        QByteArray buffer =  reply->readAll();
        QPixmap pic;
        bool ret = pic.loadFromData(buffer, "png");
        if(ret)
        {

            ui->label->setPixmap(pic.scaled(250, 250));
            qDebug() << thread->isRunning();
            if(!thread->isRunning())
            {
                thread->start();
                loginTest->setIsStop(false);
                emit ThreadStart();
            }
        }
    }
}

void MainWidget::DeelSuccess()
{
    if(thread->isRunning())
    {
        qDebug() << "deelSuccess";
        loginTest->setIsStop();
        thread->quit();
    }
    qDebug() << "Here";
    ui->labelMessage->setText("登录成功！");
    //hide();
}

void MainWidget::DeelClose()
{
    DeelSuccess();
    delete loginTest;
}

void MainWidget::DeelFinish()
{
    qDebug() << "wait";
    thread->wait();
    hide();
}
