#ifndef __INGAMEMENU_H__
#define __INGAMEMENU_H__

#include "j1Module.h"

#include "Button.h"
#include "Image.h"
#include "Scrollbar.h"

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

	void CallBack(UI_Element* element);

public:

	Image* bg_image = nullptr;

	Button* button_resume = nullptr;
	Button* button_main_menu = nullptr;

	ScrollBar* volume = nullptr;
};


#endif // __INGAMEMENU_H__