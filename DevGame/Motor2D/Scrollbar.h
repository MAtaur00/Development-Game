#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

#include "p2List.h"
#include "UI.h"
#include "Image.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class ScrollBar : public UI_Element
{
public:
	ScrollBar(int x, int y, UI_Element* parent);

	~ScrollBar() {}

	bool CleanUp();

	bool Define(SDL_Rect idle, SDL_Rect slider, char* text);

	void UI_Interaction(UI_State state);


public:

	SDL_Rect scrollbar_bar;
	SDL_Rect scrollbar_slider;

	bool clicked = false;

	SDL_Texture* tex;
};

#endif