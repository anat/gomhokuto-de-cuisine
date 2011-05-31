#ifndef NEWGAME_HPP
#define NEWGAME_HPP

#include <QDialog>

#include "Game.hpp"

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

private:
    Ui::NewGame *ui;

    Game           * _game;
    int              _winner;

public slots:

    void CompVSComp(bool);
    void CreateNewGame();
    void CancelNewGame();
    void TheWinnerIs(int);

    void SetTake(int player, int val);
    void SetReste(int player, int val);

signals:
    void SignalClear();
    void SignalWinner(int);

    void SignalTaken(int player, int val);
    void SignalReste(int player, int val);
};

#endif // NEWGAME_HPP
