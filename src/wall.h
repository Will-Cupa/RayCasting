#ifndef _WALL_H_
#define _WALL_H_
#include <SDL2/SDL.h>



class Wall{
    private:
    int x, y, size;
    
    public:
    Wall(int x, int y, int size);

    void draw(SDL_Renderer *renderer);

    bool pointColliding(int x, int y);
};

#endif