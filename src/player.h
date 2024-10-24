#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>

class Player{
    private:
    int x, y;
    int direction[2] = {0,1};

    public:
    Player(int x, int y);

    int getX();

    int getY();

    void setX(int x);

    void setY(int y);

    void addMovement(int x, int y);

    void setPos(int x, int y);

    void draw(SDL_Renderer *renderer, int size);
};

#endif