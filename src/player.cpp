#include "player.h"
#include <iostream> 

using namespace std;

Player::Player(float x, float y, int speed){
    (*this).x = x;
    (*this).y = y;
    (*this).speed = speed;

    angle, dx, dy = 0;
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

void Player::addMovement(int input){
    (*this).x += dx * input;
    (*this).y += dy * input;
}

void Player::rotate(double direction){
    angle += degToRad(direction);
    dx = cos(angle) * speed;
    dy = sin(angle) * speed;
}

void Player::draw(SDL_Renderer *renderer, int size){
    SDL_Rect rectangle = {(int)(x - size/2), (int)(y - size/2), size, size};
    
    SDL_RenderDrawLine(renderer, x, y, x + (dx*30), y + (dx* 30));
    
    SDL_RenderFillRect(renderer, &rectangle);
}

double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}