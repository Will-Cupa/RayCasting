#include "maze.h"

using namespace std;

string readFile(ifstream &file){
    string output, line;
    output = "";

    while(getline(file, line)){
        output += "\n" + line;
    };

    return output;
}

void drawMaze(SDL_Renderer *renderer, const string& maze, int wallSize, int pos_x, int pos_y){
    SDL_Rect wall;
    int x = pos_x;
    int y = pos_y;
    int j = 0;

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