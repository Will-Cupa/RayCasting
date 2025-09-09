#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include "maze.h"
#include "player.h"

using namespace std;

const int PLAYER_SPEED = 5;
const int HEIGHT = 600, WIDTH = 800;

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);
    if (init < 0){
        cerr << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    SDL_Window *window = SDL_CreateWindow("Raycast", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Window *debugWindow = SDL_CreateWindow("Debug", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == nullptr){
        cerr << "Failed to create window" << endl;
        return -1;
    }

    if (debugWindow == nullptr){
        cerr << "Failed to create debug window" << endl;
        return -1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    SDL_Renderer *debugRenderer = SDL_CreateRenderer(debugWindow, -1, SDL_RENDERER_ACCELERATED); 

    if (renderer == nullptr){
        cerr << "Failed to create renderer" << endl;
        return -2;
    }
    
    if (debugRenderer == nullptr){
        cerr << "Failed to create debug renderer" << endl;
        return -2;
    }

    bool running = true;

    SDL_Event events;

    ifstream mazeFile("maze.txt");

    Maze maze(mazeFile, 40, WIDTH/2, HEIGHT/2);

    Vector spawnCoord = maze.getPlayerSpawnPoint();

    Player player(spawnCoord.x, spawnCoord.y, PLAYER_SPEED, 10);

    while(running){
        
        int input_x = 0;
        int input_y = 0;

        //Events input
        while (SDL_PollEvent(&events)){
            switch (events.type){
                case SDL_QUIT:
                    running = false;
                    break;
                    
                //Look for a keypress 
                case SDL_KEYDOWN:
                    switch( events.key.keysym.sym ){
                                case SDLK_LEFT:
                                    input_x = -1;
                                    break;
                                case SDLK_RIGHT:
                                    input_x =  1;
                                    break;
                                case SDLK_UP:
                                    input_y =  1;
                                    break;
                                case SDLK_DOWN:
                                    input_y = -1;
                                    break;
                                default:
                                    break;
                    }
            }
        }

        //Update

        //Update position
        player.rotate(input_x*PLAYER_SPEED);
        player.addMovement(input_y);

        
        //Draw
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); //Not really clearing, more like filling
        
        SDL_SetRenderDrawColor(renderer, 0,255,255,255);
        // maze.draw(renderer);

        for(int i = 0; i < WIDTH; i++){
            // i - (WIDTH/2) -> center view around player
            float size = 100/player.castRay(WIDTH, i - (WIDTH/2), maze);
            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
            SDL_RenderDrawLine(renderer, i, HEIGHT/2 - size/2, i, HEIGHT/2 + size/2);
        }
        
        SDL_RenderPresent(renderer);

        SDL_SetRenderDrawColor(debugRenderer, 0, 0, 0, 255);
        SDL_RenderClear(debugRenderer); //Not really clearing, more like filling

        SDL_SetRenderDrawColor(debugRenderer, 0,0,200,255);
        maze.draw(debugRenderer);
        SDL_SetRenderDrawColor(debugRenderer, 255,0,0,255);
        player.draw(debugRenderer, 10);

        SDL_RenderPresent(debugRenderer);
    }

    maze.destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

//to compile
// g++ src/*.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -o bin/main

//g++ src/*.cpp -IZ:\personal\SDL2Library\include -LZ:\personal\SDL2Library\lib -lmingw32 -lSDL2main -lSDL2 -o bin/main