#ifndef INC_2DGAME_MAP_H
#define INC_2DGAME_MAP_H
#include  <string>
using namespace std;

//======================================================================================================================

/// Map class contains functions for loading/reading a map from file as well as adding tiles.
class Map {

public:

     Map( string tID , int ms , int ts );

        ~Map();
     void LoadMap( string path , int sizeX , int sizeY );
     void AddTile ( int srcX , int srcY , int xpos , int ypos );

//======================================================================================================================

private:

    string texID;
    int mapScale;
    int tileSize;
    int scaledSize;

};


#endif //INC_2DGAME_MAP_H
