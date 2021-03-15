#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"
using namespace std;

//======================================================================================================================

extern Manager manager;

Map::Map( string tID , int ms , int ts ) : texID( tID ) , mapScale( ms ) , tileSize( ts ){

    scaledSize = ms * ts;
}

//======================================================================================================================

Map::~Map() {}

//======================================================================================================================

/// Parses through tile map in "assets/tiles/map.map"

void Map::LoadMap( string path , int sizeX , int sizeY ){

    char c;
    fstream mapFile;
    mapFile.open( path );
    
    int srcX , srcY;

    for ( int y = 0 ; y < sizeY ; y++ ){

        for ( int x = 0 ; x < sizeX ; x++ ){

                mapFile.get( c );
                srcY = atoi( & c ) * tileSize ;
                mapFile.get( c );
                srcX = atoi( & c ) * tileSize ;
                AddTile( srcX , srcY , x * scaledSize , y * scaledSize );
                mapFile.ignore();

        }
        //mapFile.ignore();
    }

    mapFile.ignore();

/// Reads and parses collision map in "assets/tiles/map.map"
    for( int y = 0 ; y < sizeY ; y++) {
        for ( int x = 0 ; x < sizeX ; x++ ){

            mapFile.get( c );
            if( c == '1' ){
                auto & tcol( manager.addEntity() );
                tcol.addComponent< ColliderComponent >( "terrain" , x * scaledSize , y * scaledSize , scaledSize );
                tcol.addGroup( Game::groupColliders );
               // mapFile.ignore();
            }
            if ( c == '2'){
                auto & tcol( manager.addEntity() );
                tcol.addComponent< ColliderComponent >( "terrain2" , (x * scaledSize) , y * scaledSize , 128 , 32 );
                tcol.addGroup ( Game::groupColliders );
            }
            if ( c == '3'){
                auto & tcol( manager.addEntity() );
                tcol.addComponent< ColliderComponent >( "terrain3" , (x * scaledSize) , y * scaledSize , 128 , 64 );
                tcol.addGroup ( Game::groupColliders );
            }
            mapFile.ignore();
        }
    }

    mapFile.close();


}

//======================================================================================================================


void Map::AddTile ( int srcX , int srcY , int xpos , int ypos ){


    auto & tile( manager.addEntity() );
    tile.addComponent < TileComponent >( srcX , srcY , xpos , ypos , tileSize, mapScale , texID );
    tile.addGroup( Game::groupMap );

}


