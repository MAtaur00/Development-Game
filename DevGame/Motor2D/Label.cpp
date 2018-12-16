#include "Label.h"
#include "UI.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Menu.h"

Label::Label(int x, int y, UI_Element* parent, j1Module* CallBack) : UI_Element(x, y, parent, CallBack) {}

Label::~Label() {
	text.~p2SString();
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(this)));
	App->tex->UnLoad(texture);
}


bool Label::Update(float dt) 
{
	return true;
}

bool Label::CleanUp() {

	return true;
}
bool Label::SetText(const char* text) {

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

bool Label::Draw() {
	if (texture != nullptr)
	{
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	return true;
}