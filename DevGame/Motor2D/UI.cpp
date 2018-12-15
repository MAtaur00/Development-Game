#include "UI.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"



UI_Element::UI_Element(int x, int y, UI_Element* parent, j1Module* CallBack) : position(x, y)
{
	atlas = App->gui->GetAtlas();
	this->parent = parent;

	callback = CallBack;
}

bool UI_Element::Update(float dt) {

	return true;
}

bool UI_Element::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect);
	}
	return true;
}

bool UI_Element::CleanUp() {
	return true;
}

bool UI_Element::Intersection()
{
	bool ret = false;

	iPoint mouse;

	App->input->GetMousePosition(mouse.x, mouse.y);

	if (mouse.x > position.x && mouse.x < position.x + rect.w && 
		mouse.y > position.y && mouse.y < position.y + rect.h)
	{
		ret = true;
	}

	return ret;
}