#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <QGraphicsScene>
#include <QGraphicsView>

class GridManager
{
public:
    explicit GridManager(QGraphicsScene *);
    QGraphicsScene* currentScene;

};

#endif // GRIDMANAGER_HPP
