#ifndef __INGAMEMENU_H__
#define __INGAMEMENU_H__

#include "j1Module.h"

class Image;
class Button;

class InGameMenu : public j1Module
{
public:
	InGameMenu();
	~InGameMenu();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void CreateMenu();

public:

	Image* bg_image = nullptr;

	Button* button_continue = nullptr;
	Button* button_settings = nullptr;
	Button* button_main_menu = nullptr;
};


#endif // __INGAMEMENU_H__