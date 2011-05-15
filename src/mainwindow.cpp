#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::DrawCadre()
{
    float size = 19;
    int border = 20;
    float height = ui->gameboard->geometry().height();
    float width = ui->gameboard->geometry().width();
    float heightb = height - 2 * border;
    float widthb = width - 2 * border;
    float refh = heightb / size;
    float refw = widthb / size;
    for (int i = 1; i < size; i++)
    {
        QLine h_line(border + i * refw, border,
                     border + i * refw, height - border);
        QLine v_line(border, border + i * refh,
                     width - border, border + i * refh);
        ui->gameboard->scene()->addLine(h_line);
        ui->gameboard->scene()->addLine(v_line);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

    scene = new QGraphicsScene(5, 5,
                               ui->gameboard->geometry().width() - 10,
                               ui->gameboard->geometry().height() - 10);
    ui->gameboard->setScene(scene);
    ui->gameboard->scene()->clear();
    QImage *image = new QImage(":/Background/gazon.jpg");
    QBrush *brush = new QBrush(*image);
    scene->setBackgroundBrush(*brush);
    DrawCadre();
    update();
    QWidget::resizeEvent(event);
}
