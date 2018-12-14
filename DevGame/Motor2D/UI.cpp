#include "UI.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"



UI_Element::UI_Element(int x, int y, UI_Element* parent) : position(x, y)
{
	atlas = App->gui->GetAtlas();
	this->parent = parent;
}

bool UI_Element::Update(float dt) {

	return true;
}

bool UI_Element::Draw() {
	if (texture != nullptr)
	{
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	return true;
}

bool UI_Element::CleanUp() {
	return true;
}

bool UI_Element::MouseOnRect() {
	return true;
}
