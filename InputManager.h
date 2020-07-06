#include "Direction.h"
#include <thread>
#include <mutex>

class InputManager
{
    private:

        DIRECTION   input;                  // stores current input from user
        bool        stateFlag;              // the current state of the program
        std::mutex  inputMutex;             // serializes access to 'input'
        std::mutex  stateMutex;             // serializes access to 'bool stateFlag'

        DIRECTION   charToDirection(char);
        void        manageInput();          // takes user input and stores in 'input' (uses stateMutex & inputMutex)

    public:
    
                    InputManager();
                    ~InputManager();
        void        start();                // starts manageInput on separate thread 
        void        stop();                 // sends shutdown signal to manager thread (uses stateMutex)
        DIRECTION   getInput();             // returns the current user input and clears 'input' (uses inputMutex)
        bool        getState();             // returns if the program has been given the shutdown signal (uses stateMutex)
};