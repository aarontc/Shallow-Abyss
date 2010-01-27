#include <QtGui/QApplication>
#include "mainwindow.hpp"
#include "homescreen.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeScreen h;
    h.show();
    return a.exec();
}
