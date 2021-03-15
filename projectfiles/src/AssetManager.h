#ifndef INC_2DGAME_ASSETMANAGER_H
#define INC_2DGAME_ASSETMANAGER_H
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL2/SDL_ttf.h"


using namespace std;

/// Manager Class for handling and performing logic on Game Assets.

class AssetManager {

public:

    AssetManager ( Manager * man );
    ~AssetManager();

    ///Game Objects.

    void CreateAttack ( Vector2D pos , Vector2D vel , int range , int speed , string id , string t );
    void CreateItem ( Vector2D pos , int health , int attack , string id , string t );

    /// Texture management.
    void AddTexture ( string id , const char * path );
    SDL_Texture * GetTexture ( string id );

    void AddFont( string id , string path , int fontSize );
    TTF_Font * GetFont( string id );

private:

    Manager * manager;

    map < string , SDL_Texture * > textures;
    map < string , TTF_Font * > fonts;


};


#endif //INC_2DGAME_ASSETMANAGER_H
