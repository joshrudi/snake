#include <string>

#pragma once

class View
{
    private:

        char**  window;                         // contents of game window (aka the view)
        int     height;                         // height of the view
        int     width;                          // width of the view
        void    moveCursor(int, int);           // sets TERMINAL cursor to specific position

    public:

                View(int, int);
                ~View();
        void    refresh();                      // redraws the entire view, overwriting current output
        void    clear();                        // sets all values in view to whitespace
        void    draw(int, int, char);           // sets value at (x,y) coor to char
        void    drawBorder();                   // draws a border around the view
        void    drawString(int, std::string);   // draws string at given y coordinate
        char    read(int, int);                 // return the char value at (x,y)
        int     getHeight();
        int     getWidth();
};