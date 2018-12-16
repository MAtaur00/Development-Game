#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "UI.h"
#include "Image.h"
#include "p2List.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class CheckBox : public UI_Element
{
public:
	CheckBox(int x, int y, SDL_Rect idle, SDL_Rect click, UI_Element* parent, j1Module* CallBack);

	~CheckBox() {}

	bool CleanUp();

	bool Draw();

	bool Update(float dt);

public:
	SDL_Rect idle;
	SDL_Rect click;

	bool clicked = false;

	SDL_Texture* tex;
};

#endif