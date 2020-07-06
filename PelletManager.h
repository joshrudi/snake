#include "View.h"

class PelletManager
{
    private:

        View*       gameView;           // reference to overall game 'view' passed in through constructor
        int         currentXcoor;       // current x coor of pellet
        int         currentYcoor;       // current y coor of pellet
        void        generateNewCoor();  // randomly creates new pellet in grid location not already occupied by wall/snake/etc

    public:
    
                    PelletManager(View*);
                    ~PelletManager();
        void        update();          // checks to see if current pellet has been consumed, and makes new one if so
};