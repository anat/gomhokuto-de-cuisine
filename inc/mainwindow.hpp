#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "Game.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow * _ui;
    QGraphicsScene * _scene;
    Game           * _game;
    int              _sizeboard;
    int              _border;
    float            _refh;
    float            _refw;

    void DrawShelf(QColor &color);
    void DrawMark(QColor &color, int x, int y);
    void DrawPiece(int x, int y);
    void DrawBoard();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void print_status();
    void print_circle();

};

#endif // MAINWINDOW_H


