#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

using namespace std;

void drawMaze(SDL_Renderer *renderer, const string &maze, int wallSize, int x, int y);

string readFile(ifstream &file);

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);
    if (init <  ){
        cerr << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    SDL_Window *window = SDL_CreateWindow("Raycast", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 8  , 6  , SDL_WINDOW_SHOWN);
    
    if (window == nullptr){
        cerr << "Failed to create window" << endl;
        return -1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

    if (renderer == nullptr){
        cerr << "Failed to create renderer" << endl;
        return -2;
    }
    
    bool running = true;

    SDL_Event events;

    ifstream mazeFile("maze.txt");
    string maze = readFile(mazeFile);
    mazeFile.close();

    while(running){
        //Events input
        while (SDL_PollEvent(&events)){
            switch (events.type){
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        //Update

        //Draw
        SDL_Rect rectangle = { ,  , 4  , 2  };

        SDL_SetRenderDrawColor(renderer,  ,  ,  , 255);
        SDL_RenderClear(renderer); //not really clearing, more like filling
        
        SDL_SetRenderDrawColor(renderer,  ,2 ,255,255);
        drawMaze(renderer, maze, 4 , 3 , 5 );
        
        //SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return  ;
}

string readFile(ifstream &file){
    string output, line;
    output = "";

    while(getline(file, line)){
        output += "\n" + line;
    };

    return output;
}


void drawMaze(SDL_Renderer *renderer, const string& maze, int wallSize, int pos_x, int pos_y){
    //string maze = "XXXX\n   X\nXXXX\n";
    SDL_Rect wall;
    int x = pos_x;
    int y = pos_y;
    int j =  ;

    for(int i =  ; i < maze.length(); i++){
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

//to compile
//g++ main.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -o main