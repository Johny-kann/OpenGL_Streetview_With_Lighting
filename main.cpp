#include "mainwindow.h"
#include "openglwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    OpenGLWindow w;

    QSurfaceFormat format;
    format.setSamples(16);

    w.setFormat(format);

    w.show();

    return a.exec();
}
