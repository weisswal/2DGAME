#include "ECS.h"

/// Allows entities to be in one or more groups. Bitset indicates entities bit signature.

void Entity::addGroup( Group mGroup ){

    groupBitset [ mGroup ] = true;
    manager.AddToGroup ( this , mGroup );

}
