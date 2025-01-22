#include "player.h"

using namespace std;

Player::Player(float x, float y, int speed, float viewPlaneSize){
    (*this).x = x;
    (*this).y = y;
    (*this).speed = speed;
    (*this).viewSize = viewPlaneSize;

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

float Player::castRay(int screenWidth, int offset, const Maze& maze) {
    float rayOffset = (float)offset * ((float)viewSize/(float)screenWidth);

    struct cellInfo cell = maze.getCellFromWorldPos(x + px*rayOffset, y + py*rayOffset);


    float sx = sqrt(1+(dy/dx)*(dy/dx));
    float sy = sqrt(1+(dx/dy)*(dx/dy));

    int step_x, step_y;

    int check_x = cell.x;
    int check_y = cell.y;

    float length_x, length_y, storedLength;


    if(dx < 0){
        step_x = -1;
        length_x = sx * cell.rx;
    }else{
        step_x = 1;
        length_x = sx * (1 - cell.rx);
    }

    if(dy < 0){
        step_y = -1;
        length_y = sy * cell.ry;
    }else{
        step_y = 1;
        length_y = sy * (1 - cell.ry);
    }

    while(maze.inLayout(check_x, check_y) && !maze.isColliding(check_x, check_y)){
        if(length_x < length_y){
            check_x += step_x;
            storedLength = length_x;
            length_x += sx;
        }else{
            check_y += step_y;
            storedLength = length_y;
            length_y += sy;
        }
    }

    float collision_x = (cell.x + cell.rx) + dx * storedLength;
    float collision_y = (cell.y + cell.ry) + dy * storedLength;

    struct playerInfo pl = maze.toWorldSpace(collision_x, collision_y);

    x1 = x + px*rayOffset;
    y1 = y + py*rayOffset;

    x2 = pl.x;
    y2 = pl.y;

    return storedLength;
}

void Player::draw(SDL_Renderer *renderer, int size) const {
    SDL_Rect rectangle = {(int)(x - size/2), (int)(y - size/2), size, size};
    SDL_RenderDrawLine(renderer, x, y, x + (dx*speed*5), y + (dy*speed*5));
    SDL_RenderDrawLine(renderer, x , y , x + px*(viewSize/2),  y + py*(viewSize/2));
    SDL_RenderDrawLine(renderer, x, y, x - px*(viewSize/2),  y - py*(viewSize/2));

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    SDL_RenderFillRect(renderer, &rectangle);
}


double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}