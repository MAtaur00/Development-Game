#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Animation.h"
#include "UI.h"
#include "Label.h"
#include "Image.h"
#include "p2List.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Button : public UI_Element
{
public:
	Button(int x, int y, SDL_Rect idle, SDL_Rect hover, SDL_Rect click, UI_Element* parent);

	~Button() {}

	bool CleanUp();

	void UI_Interaction(UI_State state);

	bool Draw();

public:

	SDL_Rect button_idle;
	SDL_Rect button_hover;
	SDL_Rect button_click;

	bool clicked = false;
};

#endif