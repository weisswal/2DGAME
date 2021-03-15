#ifndef INC_2DGAME_ATTACKCOMPONENT_H
#define INC_2DGAME_ATTACKCOMPONENT_H
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

///  Initialises, Updates Attack/Enemy Components from the ECS.  Inherits from Component.

class AttackComponent : public Component {

public:

    Vector2D velocity;

    AttackComponent( int rng , int spd , Vector2D vel ) : velocity( vel ) , range( rng ) , speed( spd )  {}
    ~AttackComponent(){}

    void Init() override {

        transform = & entity -> getComponent < TransformComponent > ();
        transform -> velocity = velocity;

    }

    void Update() override {

        distance += speed;

        /// Sets bounds of attacks / projectiles on the screen.  If attack reaches max range or out of bounds
        /// its destroyed.
        if( range > distance ){

            cout << "Out of Range." << endl;
            entity -> Destroy();
        }

    }


private:

    TransformComponent * transform;
    int range = 0;
    int speed = 0;
    int distance = 0;

};

#endif //INC_2DGAME_ATTACKCOMPONENT_H
