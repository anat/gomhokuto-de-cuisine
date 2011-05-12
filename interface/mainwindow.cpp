#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

FigureEditor::FigureEditor(
        QGraphicsScene& c, QWidget* parent,
        const char* name, Qt::WindowFlags f) :
    QGraphicsView(&c,parent)
{
    setObjectName(name);
    setWindowFlags(f);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void FigureEditor::drawcadre(QGraphicsScene& c)
{
    float size = 18;
    float refh = c.height() / size;
    float refw = c.width() / size;

    for (int i = 0; i <= size; i++)
    {
        QLine l1(i * refh, 0, i * refh, c.width());

        QLine l2(0, i * refw, c.height(), i * refw);
        c.addLine(l1);
        c.addLine(l2);

    }
    std::cout << "line; h:" << c.height() << std::endl
              << "      w:" << c.width() << std::endl;
}

void FigureEditor::mousePressEvent(QMouseEvent *event)
{
    int casx =  event->pos().x() - 25;
    int casy =  event->pos().y() - 18;


    QColor color(0,0,0);
    ((MainWindow*)parent())->addCircle(casx - 15 ,casy - 18 - 15, color);

}

void FigureEditor::mouseReleaseEvent(QMouseEvent *event)
{

}

MainWindow::MainWindow(QGraphicsScene& c, QWidget* parent, Qt::WindowFlags f) :
    QMainWindow(parent, f),
    canvas(c)
{
    editor = new FigureEditor(canvas,this);

    QMenuBar* menu = menuBar();

    QMenu* file = new QMenu("&File", menu );

    file->addAction("&new");
        file->addAction("Add &Circle", this, SLOT(addCircle()), Qt::ALT+Qt::Key_C);

        menu->addMenu(file);
    QMenu* help = new QMenu("&Help", menu );
        help->addAction("&help");
        menu->addMenu(help);

    statusBar();

    editor->drawcadre(c);
    setFixedSize(c.width() + 50, c.height() + 80);
    setCentralWidget(editor);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addCircle(int x, int y, QColor &color)
{
    QAbstractGraphicsShapeItem* i = canvas.addEllipse(QRectF(0,0,30,30));
    //i->setFlag(QGraphicsItem::ItemIsMovable);
    i->setPen(Qt::NoPen);
    i->setBrush( color );
    i->setPos(x, y);
    //i->setZValue(qrand()%256);
}

void MainWindow::addCircle()
{
    QColor color(0,0,0);
    this->addCircle(qrand()%int(canvas.width()),qrand()%int(canvas.height()), color);
}
