#include "./inc/gridmanager.hpp"

GridManager::GridManager(QGraphicsScene *currentView) :
    currentScene(currentView)
{
    currentScene->setBackgroundBrush(QColor(230, 200, 167));

    //currentScene->update(); // a chaque fois que tu fais une modif
}
