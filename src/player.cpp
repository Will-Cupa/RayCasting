#include "player.h"

using namespace std;

Player::Player(float x, float y, int speed, float viewPlaneSize){
    (*this).x = x;
    (*this).y = y;
    (*this).speed = speed;
    (*this).px = viewPlaneSize/2;

    angle = 0;
}

float Player::getX(){
    return x;
}

float Player::getY(){
    return y;
}

double Player::getAngle(){
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

    double n_angle = degToRad(direction);
    float temp_px = px*cos(n_angle) - py*sin(n_angle);
    py = px*sin(n_angle) + py*cos(n_angle);

    px = temp_px;
    // px = sin(angle + degToRad(90));
    // py = -cos(angle + degToRad(90));
}

void Player::castRay(int screenWidth, Maze maze){
    for(int x = 0; x < screenWidth; x++)
    {
        pInfo playeerCell = maze.getPlayerCell(this);
        //calculate ray position and direction
        double cameraX = 2 * x / double(screenWidth) - 1; //x-coordinate in camera space (-1 to 1)
        double rayDirX = dx + px * cameraX;
        double rayDirY = dy + py * cameraX;

        double deltaDistX = abs(1 / rayDirX);
        double deltaDistY = abs(1 / rayDirY);

        double sideDistX;
        double sideDistY;

        int stepX;
        int stepY;

        bool hit;
    }
}

void Player::draw(SDL_Renderer *renderer, int size){
    SDL_Rect rectangle = {(int)(x - size/2), (int)(y - size/2), size, size};
    SDL_RenderDrawLine(renderer, x, y, x + (dx*speed*5), y + (dy*speed*5));
    SDL_RenderDrawLine(renderer, x + (dx*speed*5), y + (dy*speed*5), x + (dx*speed*5) + px,  y + (dy*speed*5) + py);
    SDL_RenderDrawLine(renderer, x + (dx*speed*5), y + (dy*speed*5), x + (dx*speed*5) - px,  y + (dy*speed*5) - py);

    SDL_RenderFillRect(renderer, &rectangle);
}


double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}