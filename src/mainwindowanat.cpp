#include "mainwindow.hpp"
#include "ui_mainwindow.h"
//#include <QtGui/QColor>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    GRID_SIZE(19)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    currentScene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(currentScene);
    gm = new GridManager(currentScene);

   std::cout << "Largeur central widget " << ui->centralWidget->geometry().width() << std::endl;
   std::cout << "Hauteur central widget " << ui->centralWidget->geometry().height() << std::endl;
   std::cout << "Largeur scene " << currentScene->width() << std::endl;
   std::cout << "Hauteur scene " << currentScene->height()  << std::endl;

    QObject::connect(currentScene, SIGNAL(sceneRectChanged( const QRectF & )), this,SLOT(gvResized( const QRectF & )));
}

MainWindow::~MainWindow()
{
    std::cout << "Largeur " << ui->centralWidget->geometry().width() << std::endl;
    std::cout << "Hauteur " << ui->centralWidget->geometry().height() << std::endl;
    std::cout << "Largeur scene " << currentScene->width() << std::endl;
    std::cout << "Hauteur scene " << currentScene->height()  << std::endl;
    delete ui;
}

void MainWindow::gvResized( const QRectF & r)
{
    std::cout << "resized !" << std::endl;
}


void MainWindow::drawGrid()
{

    float realWidth = ui->centralWidget->geometry().width() - 50;
    float realHeight = ui->centralWidget->geometry().height() - 50;

    float refh = realHeight / GRID_SIZE;
    float refw = realWidth / GRID_SIZE;

    currentScene->setSceneRect(0, 0, realWidth, realHeight);
    currentScene->clear();
    for (int i = 0; i < GRID_SIZE; i++)
    {
//        QLine l1(

        QLine l2(0, i * refw, realHeight, i * refw);
        currentScene->addLine(i * refh, 0, i * refh, realWidth);
        currentScene->addLine(l2);
    }


}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    std::cout << "Redim" << std::endl;
    std::cout << "Largeur " << ui->centralWidget->geometry().width() << std::endl;
    std::cout << "Hauteur " << ui->centralWidget->geometry().height() << std::endl;
    std::cout << "Largeur scene " << currentScene->width() << std::endl;
    std::cout << "Hauteur scene " << currentScene->height()  << std::endl;
    drawGrid();
}
