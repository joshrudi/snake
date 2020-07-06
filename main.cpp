#include "View.h"
#include "Snake.h"
#include "InputManager.h"
#include "Direction.h"
#include "PelletManager.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include <future>
#include <string>

enum MENU { EASY, MEDIUM, HARD, EXIT, UNKNOWN };

void printWelcome()
{
    std::cout << "\nWelcome to Snake! 2020 Rudaitis Software" << std::endl;
    std::cout << "\nGame Controls:" << std::endl;
    std::cout << "Up: 'W'" << std::endl;
    std::cout << "Down: 'S'" << std::endl;
    std::cout << "Left: 'A'" << std::endl;
    std::cout << "Right: 'D'" << std::endl;
    std::cout << "\nType one of the following game modes to start: 'easy', 'medium', 'hard'\nOR type 'exit' to leave" << std::endl;
}

void clearTerminal()
{
    std::cout << std::string(100, '\n');
}

void playGame(int refreshRate)
{
    clearTerminal();

    // dimensions of game view
    int height = 15;
    int width = 15;

    // init game view with border
    View* gameView = new View(height, width);
    gameView->clear();
    gameView->drawBorder();

    Snake* snake = new Snake(8, 8, gameView);

    // async gets input from user
    InputManager* inputManager = new InputManager();
    inputManager->start();

    PelletManager* pelletManager = new PelletManager(gameView);

    gameView->refresh();

    DIRECTION input = NONE;
    while (snake->checkIsAlive() && input != QUIT)
    {
        input = inputManager->getInput(); // does NOT block UI thread
        if (input == QUIT) continue;
        snake->move(input);
        pelletManager->update();
        gameView->refresh();
        usleep(refreshRate);
    }

    inputManager->stop();
    gameView->drawString(height-1, "Press Any Key...");
    gameView->refresh();

    // input manager will set the state flag when the thread has exited
    while(!inputManager->getState()) usleep(1000);

    delete snake;
    delete pelletManager;
    delete gameView;
    delete inputManager;

    clearTerminal();
}

MENU readInput()
{
    std::string input;
    MENU selection;
    std::cout << "Snake: ";
    std::cin >> input;
    
    if (input.compare("easy") == 0) selection = EASY;
    else if (input.compare("medium") == 0) selection = MEDIUM;
    else if (input.compare("hard") == 0) selection = HARD;
    else if (input.compare("exit") == 0) selection = EXIT;
    else selection = UNKNOWN;

    return selection;
}

int main()
{
    bool isRunning = true;
    
    printWelcome();

    while(isRunning)
    {
        MENU selection = readInput();

        switch (selection)
        {
            case EASY:
                playGame(600000);
                std::cout << "Thanks for playing!  Type a gamemode to play again or exit to leave :)" << std::endl;
                break;
            case MEDIUM:
                playGame(300000);
                std::cout << "Thanks for playing!  Type a gamemode to play again or exit to leave :)" << std::endl;
                break;
            case HARD:
                playGame(150000);
                std::cout << "Thanks for playing!  Type a gamemode to play again or exit to leave :)" << std::endl;
                break;
            case EXIT:
                isRunning = false;
                break;
            default:
                std::cout << "Unknown Input!" << std::endl;
                break;
        }
    }
}