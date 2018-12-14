#include "Button.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Scene.h"
#include "j1Gui.h"
#include "j1Audio.h"


Button::Button(int x, int y, UI_Element* parent) : UI_Element(x, y, parent) {}

bool Button::MouseOnRect() {
	bool ret = false;

	iPoint mouse{ 0,0 };
	App->input->GetMousePosition(mouse.x, mouse.y);

	if (mouse.x > position.x && mouse.x < position.x + rect.w) {
		if (mouse.y > position.y && mouse.y < position.y + rect.h) {
			ret = true;
		}
	}

	return ret;
}

bool Button::CleanUp() {

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

	return ret;
}