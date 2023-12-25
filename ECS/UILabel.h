#pragma once
#include "EntityComponentSystem.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"

#include "SDL.h"
/*
class UILabel : public Component {
	SDL_Rect position;
	string labelText;
	string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;

public:
	UILabel(int xpos, int ypos, string text, string font, SDL_Color& color) : 
		labelText(text) , labelFont(font) , textColor(color) {
		
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel(){
		//SDL_DestroyTexture(labelTexture);
	}
	
	void SetLabelText(string text, string font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Game::getassets()->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::getrenderer(), surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

	}
	
	void draw() override {
		SDL_RenderCopy(Game::getrenderer(), labelTexture, nullptr, &position);
	}

};*/