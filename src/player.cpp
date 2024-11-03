#include "player.h"
#include <iostream> 

using namespace std;

Player::Player(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

float Player::getX(){
    return x;
}

float Player::getY(){
    return y;
}

void Player::setX(float x){
    (*this).x = x;
}

void Player::setY(float y){
    (*this).y = y;
}

void Player::setPos(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

void Player::addMovement(int speed){
    (*this).x += direction[0] * speed;
    (*this).y += direction[1] * speed;
}

void Player::rotate(double angle){
    angle = degToRad(angle);
    double sinResult = sin(angle);
    double cosResult = cos(angle);

    direction[0] = cosResult * direction[0] - sinResult * direction[1];
    direction[1] = sinResult * direction[0] + cosResult * direction[1];
}

void Player::draw(SDL_Renderer *renderer, int size){
    SDL_Rect rectangle = {x - size/2, y - size/2, size, size};
    
    SDL_RenderDrawLine(renderer, x, y, x + (direction[0] * 30), y + (direction[1] * 30));
    
    SDL_RenderFillRect(renderer, &rectangle);
}

double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}