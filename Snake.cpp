#include "Snake.h"
#include "View.h"
#include "Direction.h"
#include <vector>
#include <iostream>

// does NOT take ownership of view
Snake::Snake(int xcoor, int ycoor, View* gv)
{
    // set head coords
    head = new BodySegment;
    head->xcoor = xcoor;
    head->ycoor = ycoor;

    // create mid point of snake body and set coords
    BodySegment* mid = new BodySegment;
    mid->xcoor = xcoor;
    mid->ycoor = ycoor+1;

    // set tail coords
    tail = new BodySegment;
    tail->xcoor = xcoor;
    tail->ycoor = ycoor+2;

    // link together nodes 
    head->next = mid;
    mid->next = tail;
    mid->prev = head;
    tail->prev = mid;
    tail->next = NULL;

    gameView = gv;
    currentDir = UP;
    isAlive = true;
    gameView->draw(head->xcoor, head->ycoor, '@');
    gameView->draw(mid->xcoor, mid->ycoor, '#');
    gameView->draw(tail->xcoor, tail->ycoor, '#');
}

Snake::~Snake()
{
    // iterate through nodes and delete snake
    BodySegment* node = head;
    while(node)
    {
        BodySegment* next = node->next;
        delete node;
        node = next;
    }
}

void Snake::move(DIRECTION newDir)
{
    // if no new input, or new Snake::DIRECTION is opposite of current Snake::DIRECTION, continue in current Snake::DIRECTION
    if (newDir == NONE || (newDir == UP && currentDir == DOWN) ||
        (newDir == DOWN && currentDir == UP) ||
        (newDir == LEFT && currentDir == RIGHT) ||
        (newDir == RIGHT && currentDir == LEFT) )
    {
        newDir = currentDir;
    }
    else // otherwise update the current diiection
    {
        currentDir = newDir;
    }

    // replace old head with new one
    gameView->draw(head->xcoor, head->ycoor, '#'); // change old head to body 'sprite'
    BodySegment* newHead = createHead(head->xcoor, head->ycoor, newDir);
    newHead->next = head;
    head->prev = newHead;
    head = newHead;

    // if head hit wall or body (collision detection)
    char headSpace = gameView->read(head->xcoor, head->ycoor);
    if (headSpace == 'X' || headSpace == '#')
    {
        isAlive = false;
    }
    else if (headSpace != '*') // if head didn't eat power pellet, remove tail
    {
        // remove tail from view
        gameView->draw(tail->xcoor, tail->ycoor, ' ');

        // remove tail from list
        BodySegment* newTail = tail->prev;
        delete tail;
        tail = newTail;
        tail->next = NULL;
    }

    // add new head to view (using head 'sprite')
    gameView->draw(head->xcoor, head->ycoor, '@');
}

BodySegment* Snake::createHead(int curx, int cury, DIRECTION dir)
{
    int newx = curx;
    int newy = cury;
    
    switch (dir)
    {
        case UP:
            newx--;
            break;
        case DOWN:
            newx++;
            break;
        case LEFT:
            newy--;
            break;
        case RIGHT:
            newy++;
            break;
        default:
            break;
    }

    BodySegment* newHead = new BodySegment;
    newHead->xcoor = newx;
    newHead->ycoor = newy;

    return newHead;
}

bool Snake::checkIsAlive()
{
    return isAlive;
}