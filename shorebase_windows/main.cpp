#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w -> setWindowFlags( Qt::SubWindow );
//   w -> setFixedSize( 1600,850 );
    w -> show();
    return a.exec();
}
