#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UI.h"
#include "j1Textures.h"
#include "SDL/include/SDL.h"
#include "p2SString.h"

struct SDL_Texture;


class Image : public UI_Element
{
public:

	Image(int x, int y, SDL_Rect image_rect, UI_Element* parent);
	~Image();

	bool Draw();


public:

	SDL_Texture* tex = nullptr;
};

#endif