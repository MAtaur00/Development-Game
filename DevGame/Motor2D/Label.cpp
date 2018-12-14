#include "Label.h"
#include "UI.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "Menu.h"

Label::Label(int x, int y, UI_Element* parent) : UI_Element(x, y, parent) {}

Label::~Label() {

}


bool Label::Update(float dt) {

	return true;
}

bool Label::CleanUp() {

	App->tex->UnLoad(texture);
	text.~p2SString();

	return true;
}
bool Label::SetText(char* text) {

	bool ret = false;

	if (texture != nullptr)
	{
		App->tex->UnLoad(texture);
	}

	SDL_Texture* tex;

	tex = App->font->Print(text, { 255, 255, 255, 255 }, App->font->fonts.start->data);
		
	if (tex != nullptr) 
	{
		uint w = 0, h = 0;
		App->tex->GetSize(tex, w, h);
		SDL_Rect rect = debug_UI = { 0, 0, (int)w, (int)h };

		texture = tex;

		this->text = text;
		this->rect = rect;

		ret = true;
	}
	return ret;
}