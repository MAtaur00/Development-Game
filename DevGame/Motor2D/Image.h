#include "UI.h"
#include "j1Textures.h"
#include "SDL/include/SDL.h"
#include "p2SString.h"

struct SDL_Texture;


class Image : public UI_Element
{
private:



public:

	Image(int x, int y, SDL_Rect image_rect, UI_Element* parent);
	~Image();


public:

	SDL_Texture* tex = nullptr;
};