#include "UI.h"
#include "Image.h"
#include "p2List.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class CheckBox : public UI_Element
{
public:
	CheckBox(int x, int y, UI_Element* parent);

	~CheckBox() {}

	bool CleanUp();

	bool Define(SDL_Rect idle, SDL_Rect click);

	void UI_Interaction(UI_State state);

public:
	SDL_Rect idle;
	SDL_Rect click;

	bool clicked = false;

	SDL_Texture* tex;
};