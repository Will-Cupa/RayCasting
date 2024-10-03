#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <fstream>

using namespace std;

class Maze{
    private :

    int wallSize;
    string layout;

    public :

    Maze(ifstream &file, int wallSize);

    void draw(SDL_Renderer *renderer, int wallSize, int x, int y);

};

string readFile(ifstream &file);

#endif