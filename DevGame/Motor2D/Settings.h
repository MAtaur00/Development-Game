#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "j1Module.h"

#include "Image.h"
#include "Scrollbar.h"
#include "CheckBox.h"
#include "Button.h"

class Settings : public j1Module
{
public:
	Settings();
	~Settings();

	bool Awake(pugi::xml_node& config);

	bool Start();

	//bool PreUpdate();

	//bool Update(float dt);

	//bool PostUpdate();

	//bool CleanUp();

	//void CreateMenu();

public:

	Image* bg_image = nullptr;

	CheckBox* vsync_checkbox = nullptr;

	ScrollBar* volume_slider = nullptr;

	Button* button_credits = nullptr;
};


#endif // __SETTINGS_H__