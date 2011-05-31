#ifndef FINALSTATE_HPP
#define FINALSTATE_HPP

#include <QDialog>

namespace Ui {
    class FinalState;
}

class FinalState : public QDialog
{
    Q_OBJECT

public:
    explicit FinalState(QWidget *parent = 0);
    ~FinalState();

private:
    Ui::FinalState *ui;

public slots:
    void AgainButton();
    void NewButton();
    void CloseButton();

signals:
    void SignalAgain();
    void SignalNew();
    void SignalClose();
};

#endif // FINALSTATE_HPP
