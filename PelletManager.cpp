#include "View.h"
#include "PelletManager.h"
#include <stdlib.h>

// does NOT take ownership of view
PelletManager::PelletManager(View* v)
{
    gameView = v;
    this->update();
}

PelletManager::~PelletManager()
{

}

void PelletManager::generateNewCoor()
{
    currentXcoor = rand() % gameView->getWidth() + 1;
    currentYcoor = rand() % gameView->getHeight() + 1;
    if (gameView->read(currentXcoor, currentYcoor) != ' ') generateNewCoor();
}

void PelletManager::update()
{
    if (gameView->read(currentXcoor, currentYcoor) != '*')
    {
        generateNewCoor();
        gameView->draw(currentXcoor, currentYcoor, '*');
    }
}