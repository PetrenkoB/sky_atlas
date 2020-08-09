//----------------------------------------------------//
//              Author:Petrenko B.
//              Date: 2018-09-28
//              Programm of determinationof solar apex
//              Known apex is situated at right ascension (RA) 18h 28m 0s and declination (dec) of 30° North
//----------------------------------------------------//


#include "mainwindow.h"
#include "widget.h"

#include <QApplication>
//#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(1000, 600);
    w.show();


    return a.exec();
}
