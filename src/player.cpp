#include "player.h"

using namespace std;

Player::Player(float x, float y, int speed, float viewPlaneSize){
    (*this).x = x;
    (*this).y = y;
    (*this).speed = speed;
    (*this).viewSize = viewPlaneSize/2;

    angle = 0;
}

float Player::getX() const{
    return x;
}

float Player::getY() const{
    return y;
}

double Player::getAngle() const{
    return angle;
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
    (*this).x += dx * input * speed;
    (*this).y += dy * input * speed;
}

void Player::rotate(double direction){
    angle += degToRad(direction);
    dx = sin(angle);
    dy = -cos(angle);

    px = sin(angle + degToRad(90));
    py = -cos(angle + degToRad(90));
}

void Player::castRay(int screenWidth, const Maze& maze) const {
    struct cellInfo pi = maze.getCellFromWorldPos(x,y);
    cout << pi.cell_x << " " << pi.cell_y << endl; 
}

void Player::draw(SDL_Renderer *renderer, int size) const {
    SDL_Rect rectangle = {(int)(x - size/2), (int)(y - size/2), size, size};
    SDL_RenderDrawLine(renderer, x, y, x + (dx*speed*5), y + (dy*speed*5));
    SDL_RenderDrawLine(renderer, x + dx, y + dy, x + dx + px*viewSize,  y + dy + py*viewSize);
    SDL_RenderDrawLine(renderer, x + dx, y + dy, x + dx - px*viewSize,  y + dy - py*viewSize);

    SDL_RenderFillRect(renderer, &rectangle);
}


double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}