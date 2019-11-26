#include "widget.h"
#include <QApplication>
#include "tray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    Tray t;
    QObject::connect(&w, &MainWidget::success, &t, &Tray::deelSuccess);
    return a.exec();
}
