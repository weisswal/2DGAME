#include "Collision.h"
#include "ECS/ColliderComponent.h"
using namespace std;
//======================================================================================================================

bool Collision::AABB( const SDL_Rect & recA , const SDL_Rect & recB ){

    /// Function for checking if two Rects overlap along the XY axis using width and height

    if ( recA.x + recA.w >= recB.x && recB.x + recB.w >= recA.x &&
         recA.y + recA.h >= recB.y && recB.y + recB.h >= recA.y ){

        return true;

    }

    return false;

}

//======================================================================================================================

bool Collision::AABB( const ColliderComponent & colA , const ColliderComponent & colB ){

    if( AABB( colA.collider , colB.collider ) ){


        /// For testing purposes.  Will let you know if you have a collision.
        //cout << colA.tag << " hit: " << colB.tag << endl;

        return true;
    }
    else {

        return false;

    }

}

