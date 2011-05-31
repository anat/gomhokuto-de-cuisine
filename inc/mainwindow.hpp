#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "Game.hpp"
#include "parameters.hpp"
#include "newgame.hpp"
#include "finalstate.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow * _ui;
    Parameters     * _param;
    NewGame        * _nGame;
    FinalState     * _finalState;
    QGraphicsScene * _scene;
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

    void SetTaken(int player, int val);


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
    void DrawAllAndModif();
    void trytopose(int x, int y);
    void ShowParameter();
    void ShowNewGame();
    void ShowError(QString*);
    void TheWinnerIs(int);

    void checkDoubleThree(int val);
    void checkFivePrize(int val);

    void SetWhoPlay(int);

signals:
    void SignalNewGame();
    void SignalPosMouse(int x, int y);
    void ReadyToDraw();
    void SignalError(QString*);

    void SignalWhoPlay(int player);
};

#endif // MAINWINDOW_H


