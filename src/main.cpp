#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include "maze.h"

using namespace std;

int px = 0;
int py = 0;

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

        int input_x = 0;
        int input_y = 0;

        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                switch( events.key.keysym.sym ){
                            case SDLK_LEFT:
                                input_x = -1;
                                break;
                            case SDLK_RIGHT:
                                input_x =  1;
                                break;
                            case SDLK_UP:
                                input_y = -1;
                                break;
                            case SDLK_DOWN:
                                input_y =  1;
                                break;
                            default:
                                break;
                }
                break;
            /*  check if key is released */
            case SDL_KEYUP:
                switch( events.key.keysym.sym ){
                            case SDLK_LEFT:
                                input_x = 0;
                                break;
                            case SDLK_RIGHT:
                                input_x =  0;
                                break;
                            case SDLK_UP:
                                input_y = 0;
                                break;
                            case SDLK_DOWN:
                                input_y =  0;
                                break;
                            default:
                                break;
                }
                break;
        }

        //Update
        
        px += input_x;

        //Draw
        SDL_Rect rectangle = {px - 10, py - 10, 20, 20};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); //not really clearing, more like filling
        
        SDL_SetRenderDrawColor(renderer, 0,255,255,255);
        drawMaze(renderer, maze, 40, 30, 50);
        
        SDL_SetRenderDrawColor(renderer, 0,240,255,255);
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

//to compile
//g++ *.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -o main

//g++ *.cpp -IZ:\personal\SDL2Library\include -LZ:\personal\SDL2Library\lib -lmingw32 -lSDL2main -lSDL2 -o main