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
    float x, y;
    int wallSize, width, height;
    int **layout;

    public :

    Maze(ifstream &file, int wallSize, int pos_x, int pos_y);

    void makeLayout(ifstream  &file);

    void initializedDimension(ifstream &file);

    void draw(SDL_Renderer *renderer) const;

    struct playerInfo getPlayerSpawnPoint() const;

    struct cellInfo getCellFromWorldPos(float x, float y) const;

    struct cellInfo getCellFromWorldPos(struct playerInfo pi) const;

    struct playerInfo toWorldSpace(float x, float y, float rx=0, float ry=0) const;

    struct playerInfo toWorldSpace(struct cellInfo ci) const;

    int** getLayout() const;

    int getX() const;

    int getY() const;

    void displayLayout() const;

    bool isColliding(int x, int y) const;

    bool inLayout(int cell_x, int cell_y) const;

    void destroy();
};

struct cellInfo{int x, y; float rx, ry;};

struct playerInfo{float x, y;};

#endif