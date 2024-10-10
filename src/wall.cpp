#include "wall.h"

Wall::Wall(int x, int y, int size){
    (*this).x = x;
    (*this).y = y;
    (*this).size = size;
}

void Wall::draw(SDL_Renderer *renderer){
    SDL_Rect rect =  {x, y, size, size};
    SDL_RenderFillRect(renderer,&rect);
}

bool Wall::pointColliding(int other_x, int other_y){
    return (other_x > this->x && other_x < this->x + size &&
            other_y > this->y && other_y < this->y + size)
}