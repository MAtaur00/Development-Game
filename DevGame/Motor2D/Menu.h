#ifndef __MENU_H__
#define __MENU_H__

#include "j1Module.h"

#include "Button.h"
#include "Image.h"

class Menu : public j1Module
{
public:
	Menu();
	~Menu();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	/*void CreateMenu();*/

	void CallBack(UI_Element* element);

public:

	Image* bg_image = nullptr;

	Label* title = nullptr;

	Button* button_continue = nullptr;
	Button* button_new_game = nullptr;
	Button* button_settings = nullptr;
	Button* button_exit = nullptr;

	bool exit = false;
};


#endif // __MENU_H__