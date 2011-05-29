#include <QDir>
#include <iostream>

#include "inc/parameters.hpp"
#include "ui_parameters.h"

Parameters::Parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parameters)
{
    ui->setupUi(this);
    _background = ":/Background/parquet.jpg";
    FillBackgroundList();

    QObject::connect(ui->BackgroundList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SetBackground(QListWidgetItem*)));
    QObject::connect(this, SIGNAL(SignalBackgroundPreview()), this, SLOT(drawBackgroundPreview()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(closeparam()));
    QObject::connect(ui->DoubleThree, SIGNAL(stateChanged(int)), this, SLOT(CheckDoubleThree(int)));
    QObject::connect(ui->FivePrize, SIGNAL(stateChanged(int)), this, SLOT(CheckFivePrize(int)));

    drawBackgroundPreview();
}

Parameters::~Parameters()
{
    delete ui;
}

QString Parameters::GetBackground()
{
    return _background;
}

void Parameters::SetBackground(QListWidgetItem* element)
{
    _background = element->text();
    emit SignalBackgroundPreview();
}

void Parameters::drawBackgroundPreview()
{
    QGraphicsScene *scene = new QGraphicsScene();
    QImage *image = new QImage(GetBackground());
    QBrush *brush = new QBrush(*image);
    ui->BackgroundPreview->setScene(scene);
    ui->BackgroundPreview->scene()->setBackgroundBrush(*brush);
}

void Parameters::closeparam()
{
    close();
    emit SignalModif();
}

void Parameters::FillBackgroundList()
{
    QDir resources(":/Background");
    QFileInfoList list = resources.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QListWidgetItem *nwItem = new QListWidgetItem(fileInfo.absoluteFilePath());
        ui->BackgroundList->addItem(nwItem);
        if (fileInfo.absoluteFilePath() == _background)
            ui->BackgroundList->setCurrentItem(nwItem);
    }
}

void Parameters::CheckDoubleThree(int val)
{
    emit SignalDoubleThree(val);
}

void Parameters::CheckFivePrize(int val)
{
    emit SignalFivePrize(val);
}
