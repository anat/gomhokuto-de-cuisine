#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "Game.hpp"
#include "parameters.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow * _ui;
    Parameters     * _param;
    QGraphicsScene * _scene;
    Game           * _game;
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
    void DrawPiece(QColor &color, int x, int y);
    void DrawPiece(QString *path);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Game& GetGame();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void print_status(QString);
    void print_status(int x, int y);
    void print_circle();
    void DrawAll();
    void trytopose(int x, int y);
    void ShowParameter();
    void TheWinnerIs(int);

    void checkDoubleThree(int val);
    void checkFivePrize(int val);

signals:
    void SignalPosMouse(int x, int y);
    void ReadyToDraw();
};

#endif // MAINWINDOW_H


