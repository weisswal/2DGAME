#ifndef INC_2DGAME_TILECOMPONENT_H
#define INC_2DGAME_TILECOMPONENT_H

#include "ECS.h"
#include "SDL2/SDL.h"
#include <string>

///  Initialises, Updates, and Tile Collider Components from the ECS.  Inherits from Component.

class TileComponent : public Component {

public:

    SDL_Texture * texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;

    TileComponent() = default;

    ~TileComponent(){

        SDL_DestroyTexture( texture );
    }

    TileComponent( int srcX , int srcY , int xpos , int ypos , int tsize, int tscale, string id ){

        texture = Game::assets -> GetTexture ( id );


        ///keeps track of player position ( actual location ; not where drawn );
        position.x = xpos;
        position.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize; //64

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale; //128

    }

    void Update() override {

        destRect.x = static_cast<float>(position.x - Game::camera.x);
        destRect.y = static_cast<float>(position.y - Game::camera.y);
    }

    void Draw() override {

        TextureManager::Draw( texture , srcRect , destRect , SDL_FLIP_NONE );
    }

};
#endif //INC_2DGAME_TILECOMPONENT_H
