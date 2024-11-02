#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <cmath>

#define PI 3.141592653589793238463

class Player{
    private:
    int x, y;
    double direction[2] = {0,1};

    public:
    Player(int x, int y);

    int getX();

    int getY();

    void setX(int x);

    void setY(int y);

    void addMovement(int speed);

    void rotate(double direction);

    void setPos(int x, int y);

    void draw(SDL_Renderer *renderer, int size);
};

double radToDeg(double radians);

double degToRad(double degrees);

#endif