#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UI.h"
#include "p2List.h"

#define CURSOR_WIDTH 2

enum UI_State;

struct UI_info
{
	UI_Element* parent = nullptr;

	fPoint position;

	int h, w;

	fPoint parent_pos;

	UI_State state;

	UI_State state_previous;

	j1Module* CallBack = nullptr;
};


class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	SDL_Texture* GetAtlas() const;

	UI_Element* AddImage(int x, int y, SDL_Rect rect, UI_Element* parent, j1Module* CallBack);

	UI_Element* AddButton(int x, int y, SDL_Rect idle, SDL_Rect hover, SDL_Rect click, char* name, UI_Element* parent, j1Module* CallBack);

	UI_Element* AddLabel(int x, int y, UI_Element* parent, j1Module* CallBack);

	UI_Element* AddCheckbox(int x, int y, SDL_Rect idle, SDL_Rect click, char* name, UI_Element* parent, j1Module* CallBack);

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

public:

	p2List<UI_Element*> UI_elements;
};

#endif // __j1GUI_H__