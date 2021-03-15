#ifndef INC_2DGAME_POSITIONCOMPONENT_H
#define INC_2DGAME_POSITIONCOMPONENT_H
#include "Components.h"
#include "../Vector2D.h"

///  Initialises, Updates, Transform Components from the ECS.  Inherits from Component.

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;
    int speed = 3;


    TransformComponent (){

        position.Zero();
    }

    explicit TransformComponent ( int sc ){

        position.Start();
        scale = sc;
    }


    TransformComponent ( int x , int y , int sc ){

        position.x = x;
        position.y = y;
        scale = sc;

    }


    TransformComponent ( float x , float y , int h , int w , int sc){

        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void Init() override{

        velocity.Zero();

    }

    void Update() override{

        ///player movement


        position.x += static_cast<int>(velocity.x * speed);
        position.y += static_cast<int>(velocity.y * speed);
    }

};


#endif //INC_2DGAME_POSITIONCOMPONENT_H
