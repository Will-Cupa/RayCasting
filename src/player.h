#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#define PI 3.141592653589793238463

class Player{
    private:
    float x, y; //player position
    float dx, dy; //direction vector
    float px, py; //view plane (1D in this case)
    int speed;
    double angle;

    public:
    Player(float x, float y, int speed, float viewPlaneSize);

    float getX();

    float getY();

    double getAngle();

    void setX(float x);

    void setY(float y);

    void addMovement(int input);

    void rotate(double direction);

    void setPos(float x, float y);

    void draw(SDL_Renderer *renderer, int size);
};

double radToDeg(double radians);

double degToRad(double degrees);

#endif