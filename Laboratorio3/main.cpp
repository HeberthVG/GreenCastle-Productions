#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication MP3_Radio(argc, argv);
    MainWindow l_App;
    l_App.showFullScreen();

    return MP3_Radio.exec();
}
