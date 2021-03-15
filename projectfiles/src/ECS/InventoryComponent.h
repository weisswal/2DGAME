#ifndef INC_2DGAME_INVENTORYCOMPONENT_H
#define INC_2DGAME_INVENTORYCOMPONENT_H
#include "SDL2/SDL.h"
#include "Components.h"
#include "../TextureManager.h"
/// Constructs and sets fields for Inventory Components from the ECS.  Inherits from Component.

class InventoryComponent : public Component {

public:

    InventoryComponent(){

        avocado = false;
        plusattack = false;
        ironfist = false;
    }

    ~InventoryComponent(){}

//======================================================================================================================


    bool GetAvocado(){
        return avocado;
    }
    bool GetPlusAttack(){
        return plusattack;
    }
    bool GetIronFist(){
        return ironfist;
    }

//======================================================================================================================

    void SetAvocado( bool status ){
        avocado = status;
    }
    void SetPlusAttack( bool status ){
        plusattack = status;
    }
    void SetIronFist( bool status ){
        ironfist = status;
    }

private:

    bool avocado;
    bool plusattack;
    bool ironfist;





};

#endif //INC_2DGAME_INVENTORYCOMPONENT_H
