#ifndef INC_2DGAME_UILABEL_H
#define INC_2DGAME_UILABEL_H
#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

///  Initialises, Updates, and Draws UILABEL Components from the ECS.  Inherits from Component.

class UILabel : public Component{

public:

    UILabel( int xpos , int ypos , string text , string font , SDL_Color & color ) :
            labelText(text) , labelFont(font) , textColor(color) {

        position.x = xpos;
        position.y = ypos;

        SetLabelText( labelText , labelFont );

    }

    ~UILabel(){}

    void SetLabelText(const string & text , const string & font ){

        SDL_Surface * surf = TTF_RenderText_Blended ( Game::assets -> GetFont( font ) , text.c_str() , textColor );
        labelTexture = SDL_CreateTextureFromSurface( Game::renderer , surf );
        SDL_FreeSurface( surf );

        SDL_QueryTexture( labelTexture , nullptr , nullptr , &position.w , &position.h);

    }

    void Draw () override {

        SDL_RenderCopy( Game::renderer , labelTexture , nullptr , &position );
        SDL_DestroyTexture(labelTexture);
    }

private:

    SDL_Rect position;
    string labelText , labelFont;
    SDL_Color textColor;
    SDL_Texture * labelTexture;



};

#endif //INC_2DGAME_UILABEL_H
