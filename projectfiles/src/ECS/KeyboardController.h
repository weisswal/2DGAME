#ifndef INC_2DGAME_KEYBOARDCONTROLLER_H
#define INC_2DGAME_KEYBOARDCONTROLLER_H
#include "../Game.h"
#include "Components.h"
#include "ECS.h"
#include "InventoryComponent.h"

/// Keyboard handler component for ECS.

class KeyboardController : public Component {

public:

    TransformComponent * transform;

    SpriteComponent * sprite;

    bool punch = false;

    void Init() override {

        transform = & entity -> getComponent < TransformComponent >();
        sprite = & entity -> getComponent < SpriteComponent >();

    }

    void Update() override {

        if (Game::event.type == SDL_KEYDOWN) {

            switch (Game::event.key.keysym.sym) {

                case SDLK_w:
                    transform -> velocity.y = -1;
                    sprite -> Play( "walkU" );
                        break;
                case SDLK_a:
                    transform -> velocity.x = -1;
                    sprite -> Play( "walkL" );
                    break;

                case SDLK_d:
                    transform -> velocity.x = 1;
                    sprite -> Play( "walkR" );
                    break;

                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite -> Play( "walkD" );
                    break;
                case SDLK_j:
                    if( punch ){
                        if( transform -> velocity.y == -1) { sprite ->Play("pUp");  }
                        if( transform -> velocity.x == -1) { sprite ->Play("pLft"); }
                        if( transform -> velocity.x ==  1) { sprite ->Play("pRt");  }
                        if( transform -> velocity.y ==  1) { sprite ->Play("pDwn"); }
                    }

                    break;

                default:
                    break;

            }

        }
        if (Game::event.type == SDL_KEYUP) {

            switch (Game::event.key.keysym.sym) {

                case SDLK_w:
                    transform->velocity.y = 0;
                    sprite -> Play( "idleU" );

                    break;

                case SDLK_a:
                    transform->velocity.x = 0;
                    sprite -> Play( "idleL" );

                    break;

                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite -> Play( "idleR" );

                    break;

                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite -> Play( "idleD" );

                    break;

                case SDLK_ESCAPE:
                    Game::isRunning = false;

                default:
                    break;

            }
        }
    }

};


#endif //INC_2DGAME_KEYBOARDCONTROLLER_H
