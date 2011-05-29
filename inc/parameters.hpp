#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <QDir>
#include <QListWidget>
#include <QDialog>

namespace Ui {
    class Parameters;
}

class Parameters : public QDialog
{
    Q_OBJECT

public:
    explicit Parameters(QWidget *parent = 0);
    ~Parameters();

    QString GetBackground();

private:
    Ui::Parameters * ui;
    QString          _background;

    void FillBackgroundList();
    void FillPieceList();

public slots:
    void SetBackground(QListWidgetItem* element);
    void drawBackgroundPreview();
    void closeparam();

signals:
    void SignalBackgroundPreview();
    void SignalModif();

};

#endif // PARAMETERS_HPP
