#include "Button.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Gui.h"


Button::Button(int x, int y, UI_Element* parent) : UI_Element(x, y, parent) {}

bool Button::CleanUp()
{
	return true;
}


bool Button::Define(SDL_Rect idle, SDL_Rect hover, SDL_Rect click, char* text)
{
	bool ret = false;

	this->idle = idle;
	this->hover = hover;
	this->click = click;
	
	label = (Label*)App->gui->AddLabel(position.x, position.y, this, nullptr);
	label->SetText(text);

	rect = idle;

	return ret;
}

void Button::UI_Interaction(UI_State state)
{
	switch (state)
	{
	case IDLE:
		rect = idle;
		break;

	case HOVER:
		rect = hover;
		break;

	case CLICK:
		rect = click;
		break;
	}
}