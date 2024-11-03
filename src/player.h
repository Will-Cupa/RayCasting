#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <cmath>

#define PI 3.141592653589793238463

class Player{
    private:
    float x, y;
    float direction[2] = {0,1};

    public:
    Player(float x, float y);

    float getX();

    float getY();

    void setX(float x);

    void setY(float y);

    void addMovement(int speed);

    void rotate(double direction);

    void setPos(float x, float y);

    void draw(SDL_Renderer *renderer, int size);
};

double radToDeg(double radians);

double degToRad(double degrees);

#endif