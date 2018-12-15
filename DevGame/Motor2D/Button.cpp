#include "Button.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Gui.h"


Button::Button(int x, int y, SDL_Rect idle, SDL_Rect hover, SDL_Rect click, UI_Element* parent) : UI_Element(x, y, parent)
{
	this->position.x = x;
	this->position.y = y;
	this->button_idle = idle;
	this->button_hover = hover;
	this->button_click = click;

	rect = idle;
}

bool Button::CleanUp()
{
	return true;
}

void Button::UI_Interaction(UI_State state)
{
	switch (state)
	{
	case IDLE:
		rect = button_idle;
		break;

	case HOVER:
		rect = button_hover;
		break;

	case CLICK:
		rect = button_click;
		break;
	}
}

bool Button::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect);
	}
	return true;
}