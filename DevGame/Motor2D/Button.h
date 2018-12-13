#include "UI.h"
#include "Label.h"
#include "Image.h"
#include "p2List.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;


class Button : public UI_Element
{
private:

public:
	Button(int x, int y, UI_Element* parent);

	~Button() {}

	bool MouseOnRect();

	bool CleanUp();

	bool Define(SDL_Rect idle, SDL_Rect hover, SDL_Rect click, char* text);


public:
	Image* image = nullptr;

	Label* label = nullptr;
	SDL_Rect idle;
	SDL_Rect hover;
	SDL_Rect click;
	bool clicked = false;
	SDL_Rect rect;

	SDL_Texture* tex;
};