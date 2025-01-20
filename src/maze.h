#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

//reading code in txt file
const int WALL = 1, SPAWN_POINT = 2;

class Maze{
    private :
    int x, y, width, height;
    int wallSize;
    int **layout;

    public :

    Maze(ifstream &file, int wallSize, int pos_x, int pos_y);

    void makeLayout(ifstream  &file);

    void initializedDimension(ifstream &file);

    void draw(SDL_Renderer *renderer) const;

    void getPlayerSpawnPoint(int coord[2]) const;

    struct cellInfo getCellFromWorldPos(float x, float y) const;

    struct cellInfo getCellFromWorldPos(struct playerInfo pi) const;

    struct playerInfo toWorldSpace(int x, int y, float rx=0, float ry=0) const;

    struct playerInfo toWorldSpace(struct cellInfo ci) const;

    int** getLayout() const;

    int getX() const;

    int getY() const;

    void displayLayout() const;

    bool isColliding(int x, int y) const;

    void destroy();
};

struct cellInfo{int cell_x, cell_y; float rx, ry;};

struct playerInfo{float x, y;};

#endif