#ifndef INC_2DGAME_ANIMATION_H
#define INC_2DGAME_ANIMATION_H


/// Sets Animation fields.

class Animation{

public:

    int index;
    int frames;
    int speed;

    Animation(){}
    Animation( int i , int f , int s ){

        index = i;
        frames = f;
        speed = s;

    }

};


#endif //INC_2DGAME_ANIMATION_H
