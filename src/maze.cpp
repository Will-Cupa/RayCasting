#include "maze.h"

void Maze::initializedDimension(ifstream &file){
    height = 0;
    width = 0;
    string line;

    while(getline(file, line)){
        if (width == 0)
            width = line.length();
        height++;
    };

    layout = new int*[height];
    for (int i = 0; i < height; i++){
        layout[i] = new int[width];
    }

    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg); // Move the file pointer to the beginning
}

void Maze::makeLayout(ifstream &file){
    string line;
    int i = 0;
    bool spawnSet = false;

    while(getline(file, line)){
        for(int j = 0; j < width; j++){
            if(line[j] == 'W'){
                layout[i][j] = WALL;
            }else if(line[j] == 'P' && !spawnSet){
                layout[i][j] = SPAWN_POINT;
                spawnSet = true;
            }else{
                layout[i][j] = 0;
            }
        }
        i++;
    };

    file.close();
}


Maze::Maze(ifstream &file, int wallSize, int pos_x, int pos_y){
    initializedDimension(file);
    makeLayout(file);

    (*this).wallSize = wallSize;
    
    //center the drawing on the coordinates
    x = pos_x - (width*wallSize)/2;
    y = pos_y - (height*wallSize)/2;
}

void Maze::draw(SDL_Renderer *renderer) const{
    int xDraw = x;
    int yDraw = y;

    //Going across the string and draw a square for each 'W'
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(layout[i][j] == WALL){
                SDL_Rect rect =  {xDraw, yDraw, wallSize, wallSize};
                SDL_RenderFillRect(renderer,&rect);
            } 
            xDraw += wallSize;
        } 
        yDraw += wallSize;
        xDraw = x;  
    }
}

void Maze::getPlayerSpawnPoint(int coord[2]) const {
    // center player in cell
    coord[0] = x + wallSize/2;
    coord[1] = y + wallSize/2;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(layout[i][j] == SPAWN_POINT){
                coord[0] += j * wallSize;
                coord[1] += i * wallSize;
            } 
        }
    }
}

int** Maze::getLayout() const{
    return (*this).layout;
}

int Maze::getX() const{
    return (*this).x;
}

int Maze::getY() const{
    return (*this).y;
}

struct cellInfo Maze::getCellFromWorldPos(float x, float y) const {
    float px = x - (*this).x;
    float py = y - (*this).y;

    float rx = fmod(px, wallSize);
    float ry = fmod(py, wallSize);

    int cell_x = px/wallSize;
    int cell_y = py/wallSize;

    return cellInfo{cell_x, cell_y, rx, ry};
}

struct playerInfo Maze::toWorldSpace(float x, float y) const{
    float px = x*wallSize + (*this).x;
    float py = y*wallSize + (*this).y;

    return playerInfo{px, py};
}

bool Maze::isColliding(int other_x, int other_y) const{
    int wall_x = x;
    int wall_y = y;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(layout[i][j] == WALL){
                if(other_x > wall_x && other_x < wall_x + wallSize &&
                other_y > wall_y && other_y < wall_y + wallSize){
                    
                    return true;
                }
            }
            wall_x += wallSize;
        }
        wall_x = x;
        wall_y += wallSize;
    }

    return false;
}

void Maze::destroy(){
    for(int i = 0; i < height; i++){
        delete[] layout[i];
    }
    delete[] layout;
}
