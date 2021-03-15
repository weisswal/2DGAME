#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <fstream>
#include <string>
#include "AssetManager.h"
#include <sstream>


using namespace std;


//Map * map;

Manager manager;

///SDL Renderer set to null because SDL has not been initialised. Will be reassigned when we instatiated renderer.

SDL_Renderer * Game::renderer = nullptr;

SDL_Event Game::event;

SDL_Rect Game::camera = { 0 , 0 , 800 , 640 };

AssetManager * Game::assets = new AssetManager( & manager );

bool Game::isRunning = false;

auto & player( manager.addEntity() );
auto & label( manager.addEntity () );

//======================================================================================================================

///Constructor
Game::Game(){}

Game::~Game(){}

//======================================================================================================================

/// Initialization function setting title of window and dimensions.

void Game::Init( const char * title , int width , int height , bool fullscreen ){

    Uint32 flags = 0;

    if( fullscreen ){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if( SDL_Init ( SDL_INIT_EVERYTHING ) == 0 ){

        cout << "Subsystems Initialised!..." << endl;


        window = SDL_CreateWindow( title , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , width , height , flags );

        if ( window ){
            cout << "Window Created!" << endl;
        }
        else{
            cout << "Window creation failed!" << endl;
                isRunning = false;
        }

        renderer = SDL_CreateRenderer( window, -1, 0 );
        if(renderer){

            SDL_SetRenderDrawColor( renderer, 255, 255, 255 ,255);
            cout << "Renderer Created!" << endl;
        }
        else{
            cout << "Renderer creation failed!" << endl;
            isRunning = false;
        }
        isRunning = true;
    }
    else {
        cout << "SDL Initialization was not successful!" << endl;
        isRunning = false;
    }

    ///Initalising entities:

    if ( TTF_Init() == -1 ){

        cout << "ERROR : SDL_TTF" << endl;

    }

    assets -> AddTexture ( "kameHouse"  , "assets/tiles/kameHouse.png"      );
    assets -> AddTexture ( "level2"     , "assets/tiles/level2.png"         );
    assets -> AddTexture ( "player"     , "assets/warrior/warriorsheet1.png");
    assets -> AddTexture ( "punch"      , "assets/warrior/redfist.png"      );
    assets -> AddTexture ( "hittest"    , "assets/warrior/hittest.png"      );
    assets -> AddTexture ( "holub"      , "assets/enemies/holub.png"        );
    assets -> AddTexture ( "holub1"     , "assets/enemies/holub.png"        );
    assets -> AddTexture ( "avocado"    , "assets/items/avocado.png"        );
    assets -> AddTexture ( "plusattack" , "assets/items/plusattack.png"     );
    assets -> AddTexture ( "ironfist"   , "assets/items/redfist.png"        );
    assets -> AddFont    ( "arial"      , "assets/arial.ttf" , 16           );


    ///Takes texture "kameHouse and slices it into 64X64pixel sprites with associated index in order to be read. Has scale
    /// of 2.
    /**
     *
     */
    if( choice == 1){

        Map map( "kameHouse" , 2 , 64 );
        map.LoadMap( "assets/tiles/map.map" , 10 , 10 );
    }

    if ( choice == 2 ){


        Map map( "kameHouse" , 2 , 64 );
        map.LoadMap( "assets/tiles/map.map" , 10 , 10 );


    }
    //Map map ( "level2" , 2 , 64);

    ///Collision map sets hit blocks around key parts of the map, can be viewed in relevant path.
    /**
     *
     */
    //map.LoadMap( "assets/tiles/map.map" , 10 , 10 );

    /// Components collected into an entity called Player and stored in a group called Players.  Transform Component
    /// gives sprite a scale of 3.  Sprite component is read and animated from sprite sheet. Keyboard controller dictates
    /// users key controls.  User controls character with { 'w', 'a', 's, 'd'} keys. Collider Component sets players hit box.



    player.addComponent < TransformComponent > ( 3 );
    player.addComponent < SpriteComponent > ( "player" , true );
    player.addComponent < KeyboardController > ();
    player.addComponent < ColliderComponent > ( "player" , 32 );
    player.addComponent < StatComponent > ( 0 , 100 , 2 );
    player.addComponent < InventoryComponent > ();
    player.addGroup( groupPlayers );

    SDL_Color white = { 255 , 255 , 255 , 255 };
    label.addComponent< UILabel >( 10 , 10 , " Health: " , "arial" , white );

    assets -> CreateAttack(Vector2D( 500 , 800 ) , Vector2D( 1 , 0 ) , 1 , 2 , "holub" , "holub"  );
    assets -> CreateAttack(Vector2D( 70 , 194 ) , Vector2D( 1 , 0 ) , 1 , 2  , "holub1" , "holub1");

    assets -> CreateItem(Vector2D( 128 , 512 ) , 20 , 0 , "avocado" , "avocado" );
    assets -> CreateItem(Vector2D( 400 , 900 ) , 5 , 2 , "plusattack" , "plusattack" );
    assets -> CreateItem(Vector2D( 835 , 902 ) , 5 , 5 , "ironfist" , "ironfist" );



}

auto & tiles ( manager.getGroup( Game::groupMap ) );
auto & players( manager.getGroup( Game::groupPlayers ) );
auto & colliders ( manager.getGroup( Game::groupColliders ) );
auto & attacks ( manager.getGroup ( Game::groupAttacks ) );
auto & items ( manager.getGroup( Game::groupItems ) );

//======================================================================================================================

void Game::handleEvents(){

    SDL_PollEvent( & event );
    switch ( event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;

    }

}

//======================================================================================================================

///Updates entities colliders and positions.

void Game::Update(){

    SDL_Rect playerCol = player.getComponent< ColliderComponent > ().collider;
    Vector2D playerPos = player.getComponent< TransformComponent >().position;

    stringstream ss;

    ss << "Health:" << player.getComponent< StatComponent >().GetHealth() << endl;

    ss << "Attack:" << player.getComponent< StatComponent >().GetAttack() << endl;

    ss << "Inventory:"<< endl;

    if( player.getComponent<InventoryComponent>().GetAvocado() == true )   { ss << "Avocado" << endl;}
    if( player.getComponent<InventoryComponent>().GetPlusAttack() == true ){ ss << "PlusAttack" << endl;}
    if( player.getComponent<InventoryComponent>().GetIronFist() == true )  { ss << "IronFist" << endl;}

    label.getComponent< UILabel >().SetLabelText( ss.str() , "arial" );

    manager.Refresh();
    manager.Update();

    ///Prevents collider pushback.  Updates players position to where he hits collider.
    for ( auto & c : colliders ){

        SDL_Rect cCol = c -> getComponent< ColliderComponent >().collider;

        if( Collision::AABB( cCol , playerCol ) ){

            player.getComponent< TransformComponent >().position = playerPos;
        }
    }

    for ( auto & i : items ){

        SDL_Rect iCol = i -> getComponent< ColliderComponent > ().collider;

        if( Collision::AABB( iCol , playerCol ) ){
            int health , attack;

            health = player.getComponent< StatComponent >().GetHealth();
            health += i -> getComponent< StatComponent >().GetHealth();
            attack = player.getComponent< StatComponent >().GetAttack();
            attack += i -> getComponent< StatComponent >().GetAttack();

            player.getComponent< StatComponent >().SetHealth( health );
            player.getComponent< StatComponent >().SetAttack ( attack );

            if ( i -> getComponent<ColliderComponent>().tag == "avocado")
                {player.getComponent<InventoryComponent>().SetAvocado( true ); }
            if ( i -> getComponent<ColliderComponent>().tag == "plusattack")
                {player.getComponent<InventoryComponent>().SetPlusAttack( true ); }
            if ( i -> getComponent<ColliderComponent>().tag == "ironfist")
                {player.getComponent<InventoryComponent>().SetIronFist( true );
                 player.getComponent<KeyboardController>().punch = true; }

            i -> Destroy();

        }
    }


    ///Detects collision between players attack and enemies and updates health of both.
    for ( auto & a : attacks ){

        SDL_Rect aCol = a -> getComponent< ColliderComponent >().collider;

        if(Collision::AABB( playerCol , aCol )){

            int pHealth , eHealth;

            pHealth = player.getComponent< StatComponent >().GetHealth();
            pHealth -= a -> getComponent< StatComponent >().GetAttack();

            eHealth  = a -> getComponent< StatComponent >().GetHealth();
            eHealth -= player.getComponent< StatComponent >().GetAttack();

            player.getComponent< StatComponent >().SetHealth( pHealth );
            a -> getComponent< StatComponent >().SetHealth ( eHealth );

        }

        /// Sets enemy movement.
        for ( auto & c : colliders ){

            SDL_Rect cCol = c -> getComponent< ColliderComponent >().collider;

            if ( Collision::AABB( aCol , cCol ) ) {

                a -> getComponent < TransformComponent >().velocity * -1;

                a -> getComponent < SpriteComponent > ().spriteFlip = SDL_FLIP_HORIZONTAL;

            }
        }
    }


    ///Sets Camera that follows player based on position.
    camera.x = static_cast<int>(player.getComponent< TransformComponent >().position.x - 400);
    camera.y = static_cast<int>(player.getComponent< TransformComponent >().position.y - 320);

    ///bounds that stop camera at edges

    if( camera.x < 0 )        { camera.x = 0; }
    if( camera.y < 0 )        { camera.y = 0; }
    if( camera.x > camera.w ) { camera.x = camera.y; }
    if( camera.y > camera.h ) { camera.y = camera.h; }




}

//======================================================================================================================

///Render function represents the typical third stage of video game code after initialization  and updating/handling events.

void Game::Render(){

    SDL_RenderClear ( renderer );
    for ( auto & t : tiles )    { t -> Draw(); }
    for ( auto & c : colliders ){ c -> Draw(); }
    for ( auto & p : players )  { p -> Draw(); }
    for ( auto & i : items )    { i -> Draw(); }
    for ( auto & a : attacks )  { a -> Draw(); }
    label.Draw();

    ///this is where we add stuff to render later
    SDL_RenderPresent ( renderer );

}

//======================================================================================================================

void Game::Save(){

    string destPath = "assets/saveData.txt";

        ofstream saveData;
        saveData.open( destPath );
        if (saveData.fail() ) { cout << "Save Failed" << endl; }

            saveData << player.getComponent< StatComponent >().GetHealth() << endl;
            saveData << player.getComponent< StatComponent >().GetAttack() << endl;
            saveData << player.getComponent< InventoryComponent >().GetAvocado() << endl;
            saveData << player.getComponent< InventoryComponent >().GetPlusAttack() << endl;
            saveData << player.getComponent< InventoryComponent >().GetIronFist() << endl;


        saveData.close();

}

//======================================================================================================================

void Game::Load(){

    string destPath = "assets/saveData.txt";
    fstream saveData;
    saveData.open( destPath );
    if (saveData.fail() ) { cout << "Load Failed" << endl; }

    string h , a , av , p , i;

    getline( saveData , h );
    getline( saveData , a );
    getline( saveData , av );
    getline( saveData , p );
    getline( saveData , i );

    int health  = stoi( h );
    int attack = stoi( a );

    player.getComponent< StatComponent >().SetHealth( health );
    player.getComponent< StatComponent >().SetAttack( attack );

    saveData.close();

    }


//======================================================================================================================



void Game::Clean()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}
