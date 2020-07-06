#include "View.h"
#include <iostream>
#include <string>

View::View(int h, int w)
{
    height = h;
    width = w;
    window = new char*[h];
    for (int y = 0; y < h; y++) window[y] = new char[w];
}

View::~View()
{
    for (int y = 0; y < height; y++) delete[] window[y];
    delete[] window;
}

void View::refresh()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            View::moveCursor(x, y);
            std::cout << window[y][x];
        }
        std::cout << '\n';
    }
}

void View::clear()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            window[y][x] = ' ';
        }
    }
}

void View::draw(int xcoor, int ycoor, char val)
{
    window[ycoor][xcoor] = val;
}

void View::drawString(int y, std::string str)
{
    if (y > height-1 || y < 0) return;
    for (int i = 1; i < height && i < str.length(); i++) window[i][y] = str[i-1];
}

void View::drawBorder()
{
    // draw veritcal walls
    for (int i = 0; i < height; i++)
    {
        this->draw(1, i, 'X');
        this->draw(width-1, i, 'X');
    }

    // draw horizontal walls
    for (int i = 0; i < width; i++)
    {
        this->draw(i, 1, 'X');
        this->draw(i, height-1, 'X');
    }
}

char View::read(int xcoor, int ycoor)
{
    char retval = '\0';
    if (xcoor >= 0 && xcoor < width && ycoor >= 0 && ycoor < width) retval = window[ycoor][xcoor];
    return retval;
}

void View::moveCursor(int x, int y)
{
    std::cout << "\033[" << x << ";" << y << "H";
}

int View::getHeight()
{
    return height;
}

int View::getWidth()
{
    return width;
}