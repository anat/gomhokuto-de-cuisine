#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>


class FigureEditor : public QGraphicsView {
    Q_OBJECT

public:
    FigureEditor(QGraphicsScene&, QWidget* parent=0, const char* name=0, Qt::WindowFlags f=0);
    void clear();
    void drawcadre(QGraphicsScene&);

signals:
    void status(const QString&);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent*event);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QGraphicsScene&, QWidget* parent=0, Qt::WindowFlags f= 0);
    ~MainWindow();
    void addCircle(int x, int y, QColor &color);

private slots:
    void addCircle();

private:
    QGraphicsScene& canvas;
    FigureEditor *editor;
    QPainter *mondessin;


};

#endif // MAINWINDOW_H
