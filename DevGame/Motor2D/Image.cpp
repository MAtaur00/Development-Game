#include "Image.h"

Image::Image(int x, int y, SDL_Rect image_rect, UI_Element* parent) : UI_Element(x, y, parent)
{
	rect = image_rect;
}

Image::~Image() {}

bool Image::Draw() {
	if (atlas != nullptr)
	{
		App->render->Blit(atlas, position.x, position.y, &rect);
	}
	return true;
}