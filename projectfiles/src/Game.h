#ifndef INC_2DGAME_GAME_H
#define INC_2DGAME_GAME_H

#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
#include "SDL2/SDL_image.h"
#include <vector>

using namespace std;

//======================================================================================================================

class ColliderComponent;
class AssetManager;

//======================================================================================================================

/// Game class contains Initialization, HandleEvents, Update, Render, Saving , Loading and Cleaning functions.  The majority
/// of game logic and assets are created/peformed here.

class Game{

public:

    Game();
    ~Game();

    void Init( const char * title, int width , int height, bool fullscreen );
    void handleEvents();
    void Update();
    void Render();
    bool Running () { return isRunning;}
    void Clean();
    void Draw();
    void Save();
    void Load();
    void AddPos( int xpos , int ypos );

    int choice;
    static SDL_Rect camera;
    static SDL_Event event;
    static bool isRunning;
    static AssetManager * assets;

    static SDL_Renderer * renderer;

    /// static instance of renderer
    enum groupLabels : size_t {

        groupMap,
        groupPlayers,
        groupColliders,
        groupAttacks,
        groupItems
    };

//======================================================================================================================

private:
    //int cnt;
    SDL_Window *window;
    int levelCounter = 0;
    int saveLevel;


};


#endif //INC_2DGAME_GAME_H
