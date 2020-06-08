

#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QLabel l;

    // On crÃ©e une vidÃ©o. Ici, c'est un GIF
    QMovie movie(":/new/prefix1/Background/gif.gif");
    // On l'associe Ã  un label
    l.setMovie (&movie);
    // On lance la vidÃ©o
    movie.start ();
    QFont V("FVF Fernando 08", 8);
    QApplication::setFont(V);

    w.show();
    return a.exec();
}
