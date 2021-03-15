#ifndef INC_2DGAME_COLLISION_H
#define INC_2DGAME_COLLISION_H
#include "SDL2/SDL.h"

//======================================================================================================================

class ColliderComponent;

/// Collision class sets up the basic maths that are used for collision.  This program implements an AABB collision structure.
class Collision {

public:

    static bool AABB( const SDL_Rect & recA , const SDL_Rect & recB );
    static bool AABB( const ColliderComponent & colA , const ColliderComponent & colB );

};
//======================================================================================================================


#endif //INC_2DGAME_COLLISION_H
