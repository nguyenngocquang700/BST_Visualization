

#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QLabel l;

    QFont V("FVF Fernando 08", 8);
    QApplication::setFont(V);

    w.show();
    return a.exec();
}
