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


Maze::Maze(ifstream &file, int wallSize, float pos_x, float pos_y){
    initializedDimension(file);
    makeLayout(file);

    (*this).wallSize = wallSize;
    
    //center the drawing on the coordinates
    pos = Vector(pos_x - (width*wallSize)/2, pos_y - (height*wallSize)/2);
}

void Maze::draw(SDL_Renderer *renderer) const{
    int xDraw = pos.x;
    int yDraw = pos.y;

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
        xDraw = pos.x;  
    }
}

Vector Maze::getPlayerSpawnPoint() const {
    //Player cell
    Vector playerCell = Vector(-1,-1);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(layout[i][j] == SPAWN_POINT){
                playerCell.x = j;
                playerCell.y = i;
            } 
        }
    }

    if(playerCell.x == -1 || playerCell.y == -1){
        throw new logic_error("Aucun point d'apparition");
    }

    // (0.5,0.5) -> Center player in cell
    return toWorldSpace(playerCell, Vector(0.5f, 0.5f));

}

int** Maze::getLayout() const{
    return (*this).layout;
}

int Maze::getX() const{
    return pos.x;
}

int Maze::getY() const{
    return pos.y;
}

struct cellInfo Maze::getCellFromWorldPos(Vector playerPos) const{
    playerPos -= (*this).pos; //implicit copy of the vector

    Vector relativePos = playerPos/(float)wallSize;

    Vector cell = trunc(relativePos);

    relativePos -= cell;

    return cellInfo{cell, relativePos};
}

Vector Maze::toWorldSpace(const struct cellInfo &cell) const{
    //On ajoute la position de la case et la position dans la case
    //On les multiplie par la taille de la case
    //On retire la position du labyrinthe
    Vector worldPos = (cell.pos+cell.relativePos)*wallSize + pos;

    return worldPos;
}

Vector Maze::toWorldSpace(float x, float y, float rx, float ry) const{
    //On ajoute la position de la case et la position dans la case
    //On les multiplie par la taille de la case
    //On retire la position du labyrinthe
    float px = (x+rx)*wallSize + pos.x;
    float py = (y+ry)*wallSize + pos.y;

    return Vector(px, py);
}

Vector Maze::toWorldSpace(const Vector &cell, const Vector &relativePos) const{
    //On ajoute la position de la case et la position dans la case
    //On les multiplie par la taille de la case
    //On retire la position du labyrinthe

    return (cell + relativePos)*wallSize + pos;
}

bool Maze::isColliding(int cell_x, int cell_y) const{
    return layout[cell_y][cell_x] == WALL;
}

bool Maze::inLayout(int cell_x, int cell_y) const{
    return cell_x < width && cell_y < height;
}

void Maze::destroy(){
    for(int i = 0; i < height; i++){
        delete[] layout[i];
    }
    delete[] layout;
}
