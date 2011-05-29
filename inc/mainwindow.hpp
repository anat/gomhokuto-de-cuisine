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
    QString          _background;
    int              _sizeboard;
    int              _border;
    float            _refh;
    float            _refw;
    float            _heightWB;
    float            _widthWB;
    float            _height;
    float            _width;

    void DrawScene();

    void InfoDraw();

    void DrawShelf(QColor &color);
    void DrawMark(QColor &color, int x, int y);
    void DrawBoard();
    void DrawPiece(int x, int y);
    void DrawPiece(QString *path);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void print_status();
    void print_status(int x, int y);
    void print_circle();
    void DrawAll();
    void trytopose(int x, int y);

signals:
    void SignalPosMouse(int x, int y);
    void ReadyToDraw();
};

#endif // MAINWINDOW_H


