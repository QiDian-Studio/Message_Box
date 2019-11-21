#ifndef LOGINTEST_H
#define LOGINTEST_H
//进程类，负责开启监控，监控是否通过二维码扫描登录
#include <QObject>
#include <QThread>
#include <QDebug>

class LoginTest : public QObject
{
    Q_OBJECT
public:
    explicit LoginTest(QObject *parent = 0);
    //进程入口函数
    void Test();

    //改变进程状态，终止进程
    void setIsStop(bool flag = true);
private:
    bool isStop;            //进程状态标志，false表示退出进程

signals:
    void success();

public slots:
};

#endif // LOGINTEST_H
