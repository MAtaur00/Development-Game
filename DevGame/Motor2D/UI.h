#ifndef __UI_H__
#define __UI_H__

#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "j1Render.h"
#include "j1App.h"

struct SDL_Texture;
enum UI_State
{
	IDLE = 1,
	HOVER = 2,
	CLICK = 3
};

class UI_Element
{

public:
	fPoint position;
	fPoint original_pos;

	SDL_Texture* atlas = nullptr;

	SDL_Texture* texture = nullptr;

	SDL_Rect debug_UI;

	SDL_Rect rect;

	UI_Element* parent;

	Animation* animation = nullptr;

	j1Module* callback = nullptr;

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

	virtual void UI_Interaction(UI_State state) {};

	bool Intersection();
};

#endif //__UI__H