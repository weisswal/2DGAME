#ifndef INC_2DGAME_STATCOMPONENT_H
#define INC_2DGAME_STATCOMPONENT_H
#include "Components.h"

///  Initialises, Updates, Stat Components from the ECS.  Inherits from Component.


class StatComponent : public Component {

public:

    StatComponent (int w , int h , int a ) {

        weight = w;
        health = h;
        attack = a;

    }
//======================================================================================================================

    ~StatComponent(){}

//======================================================================================================================

    void Init() override {

        stat = & entity -> getComponent < StatComponent > ();
        stat -> health = health;
    }

//======================================================================================================================

    void Update() override {

        if( health <= 0 ){

            entity -> Destroy();
        }
    }
//======================================================================================================================

    int GetHealth(){

        return health;
    }

    int GetAttack(){

        return attack;

    }

//======================================================================================================================

    void SetHealth( int h ){

        health = h;

    }

    void SetAttack( int a ){

        attack = a;

    }

private:

    int weight , health , attack;
    StatComponent * stat;

};


#endif //INC_2DGAME_STATCOMPONENT_H
