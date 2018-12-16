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
	ScrollBar(int x, int y, SDL_Rect bar, SDL_Rect slider, UI_Element* parent, j1Module* CallBack);

	~ScrollBar();

	bool CleanUp();

	bool Draw();

	bool Update(float dt);

public:

	SDL_Rect scrollbar_bar;
	SDL_Rect scrollbar_slider;

	bool clicked = false;

	SDL_Texture* tex;
};

#endif