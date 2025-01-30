#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <cmath>
#include "maze.h"

#define PI 3.141592653589793238463

class Player{
    private:
    float x1, x2, y1, y2; //debug variable
    float x, y; //player position
    float dx, dy; //direction vector (normalized)
    float px, py; //right vector/view plane vector (normalized)
    int speed;
    float viewSize;
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

    float castRay(int screenWidth, int offset, const Maze& maze);

    void draw(SDL_Renderer *renderer, int size) const;
};

double radToDeg(double radians);

double degToRad(double degrees);

#endif