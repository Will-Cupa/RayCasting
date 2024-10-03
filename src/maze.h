#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <fstream>

using namespace std;

class Maze{
    private :
    int x, y;
    int wallSize;
    string layout;

    public :

    Maze(ifstream &file, int wallSize, int pos_x, int pos_y);

    void draw(SDL_Renderer *renderer);

    void getPlayerSpawnPoint(int coord[2]);

};

string readFile(ifstream &file);

#endif