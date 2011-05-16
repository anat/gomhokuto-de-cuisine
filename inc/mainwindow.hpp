#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow  *ui;
    QGraphicsScene  *scene;
    int             border;
    float           refh;
    float           refw;

    void DrawCadre(QColor &color);
    void Drawrepere(QColor &color, int x, int y);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawPiece(int x, int y);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void print_status();
    void print_circle();

};

#endif // MAINWINDOW_H


