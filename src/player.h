#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <cmath>
#include "maze.h"

#define PI 3.141592653589793238463

class Player{
    private:
    float xD, yD;
    float x, y; //player position
    float dx, dy; //direction vector
    float px, py; //view plane (1D in this case)
    int speed, viewSize;
    double angle;

    public:
    Player(float x, float y, int speed, float viewPlaneSize);

    float getX() const;

    float getY() const;

    double getAngle() const;

    void setX(float x);

    void setY(float y);

    void addMovement(int input);

    void rotate(double direction);

    void setPos(float x, float y);

    void castRay(int screenWidth, const Maze& maze);

    void draw(SDL_Renderer *renderer, int size) const;
};

double radToDeg(double radians);

double degToRad(double degrees);

#endif