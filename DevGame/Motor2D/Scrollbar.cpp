#include "Scrollbar.h"
#include "UI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"
#include "Menu.h"
#include "j1Gui.h"
#include "j1Input.h"


ScrollBar::ScrollBar(int x, int y, SDL_Rect bar, SDL_Rect slider, UI_Element* parent, j1Module* CallBack) : UI_Element(x, y, parent, CallBack)
{
	this->position.x = x;
	this->position.y = y;
	this->scrollbar_bar = bar;
	this->scrollbar_slider = slider;
}

ScrollBar::~ScrollBar()
{}

bool ScrollBar::CleanUp()
{
	return true;
}

bool ScrollBar::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect);
	}
	return true;
}

bool ScrollBar::Update(float dt)
{
	if (Intersection())
	{
		if (App->input->GetMouseButtonDown(1))
		{
			if (callback)
			{
				callback->CallBack(this);
			}
		}
	}
	return true;
}