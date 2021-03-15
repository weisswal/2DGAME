#ifndef INC_2DGAME_TEXTUREMANAGER_H
#define INC_2DGAME_TEXTUREMANAGER_H
#include "Game.h"
#include <string>


/// Manager class to load and draw textures.

class TextureManager {

public:
    static SDL_Texture * LoadTexture(const char * filename );
    static void Draw( SDL_Texture* tex , SDL_Rect src , SDL_Rect dest , SDL_RendererFlip );


};

//======================================================================================================================



#endif //INC_2DGAME_TEXTUREMANAGER_H
