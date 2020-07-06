#include "InputManager.h"
#include "Direction.h"
#include <stdio.h>
#include <thread>
#include <mutex>
#include <iostream>

InputManager::InputManager()
{
    input = NONE;
    stateFlag = false;
}

InputManager::~InputManager()
{
    this->stop();
}

void InputManager::start()
{
    if (!getState())
    {
        stateFlag = true;
        std::thread (&InputManager::manageInput, this).detach();
    }
}

void InputManager::stop()
{
    stateMutex.lock();
    stateFlag = false;
    stateMutex.unlock();
}

DIRECTION InputManager::getInput()
{
    // access current user input and clears, so the current output will be null
    // until the user gives new input
    inputMutex.lock();
    DIRECTION in = input;
    input = NONE;
    inputMutex.unlock();

    return in;
}

DIRECTION InputManager::charToDirection(char c)
{
    DIRECTION dir;
    switch (c)
    {
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'q':
        dir = QUIT;
        break;
    default:
        dir = NONE;
        break;
    }
    return dir;
}

bool InputManager::getState()
{
    bool state = false;
    stateMutex.lock();
    state = stateFlag;
    stateMutex.unlock();
    return state;
}

void InputManager::manageInput()
{
    // stty raw will allow the program to take keyboard input
    // without blocking for return key
    system("stty raw");
    DIRECTION in;
    while(getState())
    {
        in = charToDirection(getchar());

        inputMutex.lock();
        input = in;
        inputMutex.unlock();
    }
    // CRITICAL to return to stty cooked
    // otherwise CTRL-C will not terminate program
    system("stty cooked");

    // set the state flag
    stateMutex.lock();
    stateFlag = true;
    stateMutex.unlock();
}