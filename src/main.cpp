#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

void drawMaze(SDL_Renderer *renderer, int wallSize);

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);
    if (init < 0){
        cerr << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    SDL_Window *window = SDL_CreateWindow("Raycast", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
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
        SDL_Rect rectangle = {0, 0, 400, 200};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); //not really clearing, more like filling
        
        SDL_SetRenderDrawColor(renderer, 0,20,255,255);
        drawMaze(renderer,40);
        
        //SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void drawMaze(SDL_Renderer *renderer, int wallSize){
    string maze = "XXXX\n000X\nXXXX\n";
    SDL_Rect wall;
    int pos_x = 0;
    int pos_y = 0;
    int j = 0;

    for(int i = 0; i < maze.length(); i++){
        if(maze[i] == '\n'){
            pos_y += wallSize;
            pos_x = 0;
        } else {
            if(maze[i] == 'X'){
                wall = {pos_x, pos_y, wallSize, wallSize};
                SDL_RenderFillRect(renderer, &wall);
            } 
            
            pos_x += wallSize;
        }   
    }

}

//to compile
//g++ main.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -o main