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
    return pos.x;
}

float Player::getY() const{
    return pos.y;
}

double Player::getAngle() const{
    return angle;
}

void Player::setX(float x){
    pos.x = x;
}

void Player::setY(float y){
    pos.y = y;
}

void Player::setPos(float x, float y){
    pos.x = x;
    pos.y = y;
}

void Player::addMovement(int input){
    pos += dir * input * speed;
}

void Player::rotate(double direction){
    angle += degToRad(direction);
    dir.x = sin(angle);
    dir.y = -cos(angle);

    plane.x = sin(angle + degToRad(90));
    plane.y = -cos(angle + degToRad(90));
}

float Player::castRay(int screenWidth, int offset, const Maze& maze) {
    float rayOffset = offset * (viewSize/screenWidth);

    struct cellInfo cell = maze.getCellFromWorldPos(pos + plane*rayOffset);

    //length increment
    float sx = sqrt(1+(dir.y/dir.x)*(dir.y/dir.x));
    float sy = sqrt(1+(dir.x/dir.y)*(dir.x/dir.y));

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

    float collision_x = (cell.x + cell.rx) + dir.x * storedLength;
    float collision_y = (cell.y + cell.ry) + dir.y * storedLength;

    struct playerInfo pl = maze.toWorldSpace(collision_x, collision_y);

    x1 = pos.x + plane.x*rayOffset;
    y1 = pos.y + plane.y*rayOffset;

    x2 = pl.x;
    y2 = pl.y;

    Vector rayDir = dir + plane * offset;

    return storedLength;
}

void Player::draw(SDL_Renderer *renderer, int size) const {
    SDL_Rect rectangle = {pos.x - size/2, pos.y - size/2, size, size};
    SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + (dir.x*speed*5), pos.y + (dir.y*speed*5));
    SDL_RenderDrawLine(renderer, pos.x , pos.y , pos.x + plane.x*(viewSize/2),  pos.y + plane.y*(viewSize/2));
    SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x - plane.x*(viewSize/2),  pos.y - plane.y*(viewSize/2));

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    SDL_RenderFillRect(renderer, &rectangle);
}


double radToDeg(double radians){
    return radians * (180.0/PI);
}

double degToRad(double degrees){
    return degrees * (PI/180.0);
}

