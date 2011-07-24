#ifndef NEWGAME_HPP
#define NEWGAME_HPP

#include <QDialog>
#include "Game.hpp"
#include <QNetworkInterface>
#include <QTcpSocket>

namespace Ui {
    class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0);
    ~NewGame();

    Game * getGame();
    bool    isNetworkGame() { return _isNetworkGame; }
private:
    Ui::NewGame*    ui;
    Game*           _game;
    int              _winner;
    bool            _isNetworkGame;
    int             _createOrJoin;
public slots:

    void CompVSComp(bool);
    void NetworkGame(bool);
    void isNetwork(bool);
    void CreateNewGame();
    void Join();
    void Create();
    void CancelNewGame();
    void TheWinnerIs(int);
    void refreshGames();
signals:
    void SignalClear();
    void SignalWinner(int);
};

#endif // NEWGAME_HPP
