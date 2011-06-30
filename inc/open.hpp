#ifndef OPEN_HPP
#define OPEN_HPP

#include <QDialog>

namespace Ui {
    class Open;
}

class Open : public QDialog
{
    Q_OBJECT

public:
    explicit Open(QWidget *parent = 0);
    ~Open();

private:
    Ui::Open *ui;
};

#endif // OPEN_HPP
