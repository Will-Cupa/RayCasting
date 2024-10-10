#include "maze.h"
using namespace std;

int** Maze::readFile(ifstream &file){
    string line, output;
    height = 0;
    width = 0;

    while(getline(file, line)){
        if (width == 0)
            width = line.length();
        height++;
    };
    
    // Reset file pointer to the beginning
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg); // Move the file pointer to the beginning

    layout = new int*[height];
    for (int i = 0; i < height; i++){
        layout[i] = new int[width];
    }

    int i = 0;

    // Second pass: populate the layout
    while(getline(file, line)){
        for(int j = 0; j < width; j++){
            if(line[j] == 'W'){
                layout[i][j] = 1;
            }else{
                layout[i][j] = 0;
            }
        }
        i++;
    };

    file.close();
    return layout;
}


Maze::Maze(ifstream &file, int wallSize, int pos_x, int pos_y){
    layout = readFile(file);
    (*this).wallSize = wallSize;
    x = pos_x;
    y = pos_y;
}

void Maze::draw(SDL_Renderer *renderer){
    //center the drawing on the coordinates
    int pos_x = x - (width*wallSize)/2;
    int pos_y = y - (height*wallSize)/2 - wallSize;

    int x = pos_x;
    int y = pos_y;

    //Going across the string and draw a square for each 'W'
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(layout[i][j]){
                SDL_Rect rect =  {x, y, wallSize, wallSize};
                SDL_RenderFillRect(renderer,&rect);
            } 
            x += wallSize;
        } 
        y += wallSize;
        x = pos_x;  
    }
}

void Maze::getPlayerSpawnPoint(int coord[2]){
    coord[0] = 1;
    coord[1] = 2;
    /*
    for(int i = 0; i < layout.length(); i++){
        if(layout[i] == 'P'){
            return *coord;
        }
    }
    */
}

void Maze::displayLayout(){
    for(int i = 0; i < height; i++){
        cout << "|";
        for(int j = 0; j < width; j++){
            cout << layout[i][j] << "|";
        }  
        cout << endl;
    }
}