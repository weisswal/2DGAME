#include <iostream>
#include <iostream>
#include "Game.h"

//======================================================================================================================

/// Main game loop.  While the boolean Running is true the game will be playable.


Game *game = nullptr;

int main( ) {

    /// Frames per second for target frame. 60 is closest to refresh rate of monitor
    const int FPS = 60;

    /// How long a frame takes. max time between frames.
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    Uint32 frameTime;

    Game game;

    cout << "Press 1 to Start New Game" << "    " << "Press 2 to Continue" << endl;
    cin >> game.choice;
    if( game.choice < 1 || game.choice > 2 ){
        cout << "Invalid option. Please press 1 or 2!" << endl;
    }

    if(game.choice == 1){

        game.Init( "GameEngine" , 800 , 640 , false );

        while ( game.Running() ){

            frameStart = SDL_GetTicks();

            game.handleEvents();
            game.Update();
            game.Render();

            frameTime = SDL_GetTicks() - frameStart;

            if ( frameDelay > frameTime ){

                SDL_Delay( frameDelay - frameTime);
            }
        }

        game.Save();

        game.Clean();


    }
    if (game.choice == 2 ){

        game.Init( "GameEngine" , 800 , 640 , false );


        game.Load();

        while ( game.Running() ){

            frameStart = SDL_GetTicks();

            game.handleEvents();
            game.Update();
            game.Render();

            frameTime = SDL_GetTicks() - frameStart;

            if ( frameDelay > frameTime ){

                SDL_Delay( frameDelay - frameTime);
            }
        }

        game.Save();

        game.Clean();


    }


    return 0;
}