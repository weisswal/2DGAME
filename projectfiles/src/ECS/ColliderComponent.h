#ifndef INC_2DGAME_COLLIDERCOMPONENT_H
#define INC_2DGAME_COLLIDERCOMPONENT_H
#include <string>
#include "SDL2/SDL.h"
#include "Components.h"
#include "../TextureManager.h"
#include "../Collision.h"
#include "../AssetManager.h"

///  Initialises, Updates, and Draws Collider Components from the ECS.  Inherits from Component.

class ColliderComponent : public Component {

public:

    SDL_Rect collider;
    string tag;
    SDL_Texture * tex;
    SDL_Rect srcR , destR;
    TransformComponent * transform;

    ColliderComponent( std::string t ){

        tag = t;
    }

    ColliderComponent ( string t , int size ){
        tag = t;
        collider.h = collider.w = size;
    }

    ColliderComponent ( string t , int xpos , int ypos , int h , int w ){
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = h;
        collider.w = w;
    }

    ColliderComponent ( string t , int xpos , int ypos , int size ){
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void Init() override{

        transform = & entity -> getComponent < TransformComponent >();

        tex = TextureManager::LoadTexture( "assets/tiles/collision.png" );

        srcR =  { 0 , 0 , 32 , 32 };
        destR = { collider.x , collider.y , collider.w , collider.h };


    }

    void Update() override {


        if( tag == "player" ){

            collider.x = static_cast <int> (transform -> position.x + 32 );
            collider.y = static_cast <int> (transform -> position.y + 32 );
            collider.w = 32;
            collider.h = 32;

        }

        if( tag == "holub" ){

            collider.x = static_cast <int> ( transform -> position.x );
            collider.y = static_cast <int> ( transform -> position.y );
            collider.w = transform -> width;
            collider.h = transform -> height;

        }
        if( tag == "holub1" ){

            collider.x = static_cast <int> ( transform -> position.x );
            collider.y = static_cast <int> ( transform -> position.y );
            collider.w = transform -> width;
            collider.h = transform -> height;

        }
        if( tag == "punch" ){

            collider.x = static_cast <int> ( transform -> position.x + 32 );
            collider.y = static_cast <int> ( transform -> position.y + 32 );
            collider.w = 48;
            collider.h = 48;

        }
        if( tag == "avocado" ){

            collider.x = static_cast <int> ( transform -> position.x );
            collider.y = static_cast <int> ( transform -> position.y );
            collider.w = transform -> width;
            collider.h = transform -> height;

        }

        if( tag == "plusattack" ){

            collider.x = static_cast <int> ( transform -> position.x );
            collider.y = static_cast <int> ( transform -> position.y );
            collider.w = transform -> width;
            collider.h = transform -> height;

        }
        if( tag == "ironfist" ){

            collider.x = static_cast <int> ( transform -> position.x );
            collider.y = static_cast <int> ( transform -> position.y );
            collider.w = transform -> width;
            collider.h = transform -> height;

        }

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void Draw() override {

        /// Shows collision blocks.
        //TextureManager::Draw( tex , srcR , destR , SDL_FLIP_NONE );
    }

};


#endif //INC_2DGAME_COLLIDERCOMPONENT_H
