#include "CheckBox.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Gui.h"


CheckBox::CheckBox(int x, int y, UI_Element* parent) : UI_Element(x, y, parent) {}

bool CheckBox::CleanUp()
{
	return true;
}


bool CheckBox::Define(SDL_Rect idle, SDL_Rect click)
{
	bool ret = false;

	this->idle = idle;
	this->click = click;

	rect = idle;

	return ret;
}

void CheckBox::UI_Interaction(UI_State state)
{
	switch (state)
	{
	case IDLE:
		rect = idle;
		break;

	case CLICK:
		rect = click;
		break;
	}
}