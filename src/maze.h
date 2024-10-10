#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include "wall.h"

using namespace std;

const int WALL = 1, SPAWN_POINT = 2;

class Maze{
    private :
    int x, y, width, height;
    int wallSize;
    int **layout;

    public :

    Maze(ifstream &file, int wallSize, int pos_x, int pos_y);

    void makeLayout(ifstream &file);

    void initializedDimension(ifstream &file);

    void draw(SDL_Renderer *renderer);

    void getPlayerSpawnPoint(int coord[2]);

    void displayLayout();

    bool isColliding(int x, int y);
};

#endif