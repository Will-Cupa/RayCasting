#include "player.h"

Player::Player(int x, int y){
    (*this).x = x;
    (*this).y = y;
}

int Player::getX(){
    return x;
}

int Player::getY(){
    return y;
}

void Player::setX(int x){
    (*this).x = x;
}

void Player::setY(int y){
    (*this).y = y;
}

void Player::setPos(int x, int y){
    (*this).x = x;
    (*this).y = y;
}

void Player::addMovement(int speed_x, int speed_y){
    (*this).x += direction[0]*speed_x;
    (*this).y += direction[1]*speed_y;
}

void Player::draw(SDL_Renderer *renderer, int size){
    SDL_Rect rectangle = {x - size/2, y - size/2, size, size};

    SDL_RenderFillRect(renderer, &rectangle);
}