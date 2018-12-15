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

	/*bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void CreateMenu();*/

public:

	Image* bg_image = nullptr;

	Button* button_continue = nullptr;
	Button* button_new_game = nullptr;
	Button* button_settings = nullptr;
	Button* button_credits = nullptr;
	Button* button_exit = nullptr;
};


#endif // __MENU_H__