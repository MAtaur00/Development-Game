#include "Image.h"

Image::Image(int x, int y, SDL_Rect image_rect, UI_Element* parent, j1Module* CallBack) : UI_Element(x, y, parent, CallBack)
{
	rect = image_rect;
}

Image::~Image() {}

bool Image::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect, 0.0f);
	}
	return true;
}