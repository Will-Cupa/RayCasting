#include "maze.h"
#include <iostream>
using namespace std;

string readFile(ifstream &file){
    string output, line;
    output = "";
    int width = 0;
    int height = 0;

    while(getline(file, line)){
        if (width == 0)
            width = line.length();
        output += "\n" + line;
        height++;
    };
    return output + (char)width + (char)height;
}

void drawMaze(SDL_Renderer *renderer, const string& maze, int wallSize, int pos_x, int pos_y){
    SDL_Rect wall;
    int mazeWidth = (int)maze[maze.length()-2];
    int mazeHeight = (int)maze[maze.length()-1];

    pos_x -= (mazeWidth*wallSize)/2;
    pos_y -= (mazeHeight*wallSize)/2 + wallSize;

    int x = pos_x;
    int y = pos_y;

    for(int i = 0; i < maze.length(); i++){
        if(maze[i] == '\n'){
            y += wallSize;
            x = pos_x;
        } else {
            if(maze[i] == 'W'){
                wall = {x, y, wallSize, wallSize};
                SDL_RenderFillRect(renderer, &wall);
            } 
            x += wallSize;
        }   
    }

}