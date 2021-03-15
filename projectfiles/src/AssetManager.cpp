#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager ( Manager * man ) : manager( man ){

}

AssetManager::~AssetManager(){

}

void AssetManager::CreateAttack ( Vector2D pos , Vector2D vel , int range , int speed , string id , string t ){

    auto & attacks( manager -> addEntity() );
    attacks.addComponent< TransformComponent > ( pos.x , pos.y , 48 , 48 , 1 );
    attacks.addComponent< SpriteComponent > ( id , false );
    attacks.addComponent< AttackComponent > ( range , speed , vel );
    attacks.addComponent< ColliderComponent > ( t );
    attacks.addComponent< StatComponent > ( 0 , 20 , 2 );
    attacks.addGroup( Game::groupAttacks );
}

void AssetManager::CreateItem ( Vector2D pos , int health , int attack , string id , string t ){

    auto & items( manager -> addEntity() );
    items.addComponent< TransformComponent >( pos.x , pos.y , 32 , 32 , 1 );
    items.addComponent< SpriteComponent > ( id , false );
    items.addComponent< ColliderComponent >( t , 32 );
    items.addComponent< StatComponent >( 1 , health , attack );
    items.addGroup ( Game::groupItems );
}


void AssetManager::AddTexture( string id , const char *path ) {

    textures.emplace( id , TextureManager::LoadTexture( path ) );
}

SDL_Texture * AssetManager::GetTexture( string id ) {

    return textures[ id ];
}

void AssetManager::AddFont( string id , string path , int fontSize ){

    fonts.emplace( id , TTF_OpenFont( path.c_str() , fontSize ) );

}

TTF_Font * AssetManager::GetFont( string id ){

    return fonts[id];

}