#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow  *ui;
    QGraphicsScene  *scene;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawCadre();
    void Drawrepere(int x, int y);



protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // MAINWINDOW_H
