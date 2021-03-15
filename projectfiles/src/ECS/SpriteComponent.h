#ifndef INC_2DGAME_SPRITECOMPONENT_H
#define INC_2DGAME_SPRITECOMPONENT_H

#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include <string>
#include "../AssetManager.h"

using namespace std;

///  Initialises, Updates, and Draws Sprite Components from the ECS.  Inherits from Component.

class SpriteComponent : public Component {


private:

    TransformComponent * transform;
    SDL_Texture * texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:


    int animIndex = 0;

    map < const char * , Animation > animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    /// path to texture that will be used.
    SpriteComponent( string id ) {

        setTex( id );
    }

    SpriteComponent( string id , bool isAnimated  ) {

        animated = isAnimated;

        Animation idleD  = Animation ( 0 , 1 , 1 );
        Animation idleL  = Animation ( 1 , 1 , 1 );
        Animation idleR  = Animation ( 2 , 1 , 1 );
        Animation idleU  = Animation ( 3 , 1 , 1 );

        Animation walkD = Animation ( 0 , 4 , 100 );
        Animation walkL = Animation ( 1 , 4 , 100 );
        Animation walkR = Animation ( 2 , 4 , 100 );
        Animation walkU = Animation ( 3 , 4 , 100 );

        Animation pUp   = Animation ( 4 , 1 , 100 );
        Animation pDwn  = Animation ( 5 , 1 , 100 );
        Animation pLft  = Animation ( 6 , 1 , 100 );
        Animation pRt   = Animation ( 7 , 1 , 100 );
        Animation none  = Animation ( 8 , 1 , 1   );


        animations.emplace( "idleD" , idleD );
        animations.emplace( "idleL" , idleL );
        animations.emplace( "idleR" , idleR );
        animations.emplace( "idleU" , idleU );

        animations.emplace( "walkD" , walkD );
        animations.emplace( "walkL" , walkL );
        animations.emplace( "walkR" , walkR );
        animations.emplace( "walkU" , walkU );

        animations.emplace( "pUp"   , pUp   );
        animations.emplace( "pDwn"  , pDwn  );
        animations.emplace( "pLft"  , pLft  );
        animations.emplace( "pRt"   , pRt   );
        animations.emplace( "none"  , none  );

        Play( "idleD" );

        setTex( id );


    }

    ~SpriteComponent(){

        ///SDL_DestroyTexture( texture );
    }

    void setTex ( string id ){

        texture = Game::assets -> GetTexture ( id );

    }

    ///initialize rectangles
    void Init() override {

        transform = &entity -> getComponent < TransformComponent > ();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform -> width * 2;
        srcRect.h = transform -> height * 2;
        destRect.w = destRect.h = 64;

    }
    /// updates destination rectangles position.

    void Update() override {

        if ( animated ){
            srcRect.x = srcRect.w * static_cast < int > (( SDL_GetTicks() / speed ) % frames );
        }

        srcRect.y = animIndex * transform -> height * 2;

        destRect.x = static_cast<int>( transform -> position.x ) - Game::camera.x;
        destRect.y = static_cast<int>( transform -> position.y ) - Game::camera.y;
        destRect.w = transform -> width * transform -> scale;
        destRect.h = transform -> height * transform -> scale;

    }

    void Draw() override {

        TextureManager::Draw( texture , srcRect , destRect , spriteFlip );

    }

    void Play( const char * animName ){

        frames = animations[ animName ].frames;
        animIndex = animations[ animName ].index;
        speed = animations[ animName ].speed;


    }




};



#endif //INC_2DGAME_SPRITECOMPONENT_H
