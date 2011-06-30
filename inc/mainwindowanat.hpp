#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "gridmanager.hpp"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGrid();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* currentScene;
    GridManager* gm;
    void resizeEvent(QResizeEvent *event);
    const int GRID_SIZE;
protected slots:
    void gvResized( const QRectF & );
};

#endif // MAINWINDOW_H
