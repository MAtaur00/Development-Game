#include "InGameMenu.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "Brofiler/Brofiler.h"

InGameMenu::InGameMenu()
{
	name.create("inGameMenu");
}

InGameMenu::~InGameMenu() {}

bool InGameMenu::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

bool InGameMenu::Start()
{
	//bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 640, 480 }, NULL, this);

	button_continue = (Button*)App->gui->AddButton(0, 0, { 998, 45, 246, 61 }, { 998, 301, 246, 61 }, { 998, 164, 246, 61 }, "Resume", NULL, this);
	button_main_menu = (Button*)App->gui->AddButton(0, 0, { 1295, 46, 246, 59 }, { 1295, 302, 246, 59 }, { 1295, 165, 246, 59 }, "Main Menu", NULL, this);

	//volume = (ScrollBar*)App->gui->AddScrollbar(0, 0, { 1393, 521, 246, 41 }, { 1663, 514, 52, 48 }, NULL, this);

	return true;
}

bool InGameMenu::PreUpdate()
{
	return true;
}