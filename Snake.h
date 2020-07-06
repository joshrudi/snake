#include "View.h"
#include "Direction.h"

// individual body segment of snake (node in Linked List)
struct BodySegment
{
    int                 xcoor;                              // x coordinate of node in view
    int                 ycoor;                              // y coordinate of node in view
    BodySegment*        next;
    BodySegment*        prev;  
};

class Snake
{
    private:

        View*           gameView;                           // reference to overall game 'view' passed in through constructor
        BodySegment*    head;                               // head of the snake
        BodySegment*    tail;                               // tail of the snake
        DIRECTION       currentDir;                         // direction snake is currently 'facing'
        bool            isAlive;                            // false if snake hit a wall or body segment

    public:
    
                        Snake(int, int, View*);             // saves reference of external game 'view' to write snake updates to, does NOT take ownership
                        ~Snake();
        void            move(DIRECTION);                    // updates view to represent movement of snake, sets 'isAlive' to false if collision
        BodySegment*    createHead(int, int, DIRECTION);    // creates new head location based on direction of snake
        bool            checkIsAlive();                     // return true if snake is still alive
};