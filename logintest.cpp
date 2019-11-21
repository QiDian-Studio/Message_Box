#include "logintest.h"

LoginTest::LoginTest(QObject *parent)
    : QObject(parent)
    , isStop(false)
{

}

void LoginTest::Test()
{
    qDebug() << "Test()" << ": isStop = " << isStop;
    while(isStop == false)
    {
        QThread::sleep(3);  //模拟匹配过程，三秒后表示登录成功
        emit success();     //匹配成功
        QThread::sleep(1);
    }
}

void LoginTest::setIsStop(bool flag)
{
    isStop = flag;
}
