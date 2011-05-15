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

    void DrawCadre(QColor &color);
    void Drawrepere(QColor &color, int x, int y);

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
void print_status();


};

#endif // MAINWINDOW_H
