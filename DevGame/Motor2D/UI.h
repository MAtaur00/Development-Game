#ifndef __UI_H__
#define __UI_H__

#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "j1Render.h"
#include "j1App.h"

struct SDL_Texture;

class UI_Element
{

public:
	fPoint position;

	SDL_Texture* atlas = nullptr;

	SDL_Texture* texture = nullptr;

	SDL_Rect debug_UI;

	SDL_Rect rect;

	UI_Element* parent;

	j1Module* callback = nullptr;

	bool destroy = false;

public:

	//Constructor
	UI_Element() {}
	UI_Element(int x, int y, UI_Element* parent, j1Module* CallBack);

	//Destructor
	virtual ~UI_Element() {}

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called each loop iteration
	virtual bool Draw();

	// Called before quitting
	virtual bool CleanUp();

	bool Intersection();
};

#endif //__UI__H