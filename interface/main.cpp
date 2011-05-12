#include <QStatusBar>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QTimer>

#include "mainwindow.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene canvas;

    canvas.setSceneRect(0, 0, 600, 600);
    MainWindow m(canvas);
    //m.setBaseSize(600, 625);
   // m.resize(m.sizeHint());
    m.setWindowTitle("Gomoku");

    m.show();

    return a.exec();
}
