#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <fstream>

using namespace std;

void drawMaze(SDL_Renderer *renderer, const string &maze, int wallSize, int x, int y);

string readFile(ifstream &file);

#endif