#include "Button.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Gui.h"
#include "j1Input.h"


Button::Button(int x, int y, SDL_Rect idle, SDL_Rect hover, SDL_Rect click, UI_Element* parent, Label* name, j1Module* CallBack) : UI_Element(x, y, parent, CallBack)
{
	this->position.x = x;
	this->position.y = y;
	this->button_idle = idle;
	this->button_hover = hover;
	this->button_click = click;

	rect = idle;

	text = name;
}

Button::~Button()
{
	//App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(this)));
	//delete text;
}

bool Button::CleanUp()
{
	return true;
}

bool Button::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect);
	}
	return true;
}

bool Button::Update(float dt)
{
	if (Intersection())
	{
		rect = button_hover;
		if (App->input->GetMouseButtonDown(1))
		{
			rect = button_click;
			if (callback)
			{
				callback->CallBack(this);
			}
		}
	}
	else rect = button_idle;

	return true;
}