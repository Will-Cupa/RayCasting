#include "player.h"

using namespace std;

Player::Player(float x, float y, int speed, float viewPlaneSize){
    (*this).x = x;
    (*this).y = y;
    (*this).speed = speed;
    (*this).viewSize = viewPlaneSize/2;

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

    px = sin(angle + degToRad(90));
    py = -cos(angle + degToRad(90));
}

void Player::castRay(int screenWidth, Maze maze){
    for(int screenX = 0; screenX < screenWidth; screenX++)
    {
        pInfo playerCell = maze.getCellFromWorldPos(x,y);
        int mapX = playerCell.cell_x;
        int mapY = playerCell.cell_y;

        cout << playerCell.rx << " " << playerCell.ry << endl;

        //calculate ray position and direction
        double cameraX = 2 * screenX / double(screenWidth) - 1; //x-coordinate in camera space (-1 to 1)
        double rayDirX = dx + px * viewSize * cameraX;
        double rayDirY = dy + py * viewSize * cameraX;

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