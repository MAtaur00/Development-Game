#include "Menu.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "Brofiler/Brofiler.h"

Menu::Menu()
{
	name.create("menu");
}

Menu::~Menu() {}

bool Menu::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

bool Menu::Start()
{
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 640, 480 }, NULL, this);

	button_continue = (Button*)App->gui->AddButton(200, 350, { 998, 45, 246, 61 }, { 998, 164, 246, 61 }, { 998, 301, 246, 61 }, "Continue", NULL, this);
	button_new_game = (Button*)App->gui->AddButton(550, 350, { 998, 45, 246, 61 }, { 998, 164, 246, 61 }, { 998, 301, 246, 61 }, "New Game", NULL, this);
	button_settings = (Button*)App->gui->AddButton(200, 500, { 998, 45, 246, 61 }, { 998, 164, 246, 61 }, { 998, 301, 246, 61 }, "Settings", NULL, this);
	button_exit = (Button*)App->gui->AddButton(550, 500, { 1295, 46, 246, 59 }, { 1295, 165, 246, 59 }, { 1295, 302, 246, 59 }, "Exit", NULL, this);

	return true;
}

bool Menu::PreUpdate()
{
	return true;
}

bool Menu::Update(float dt)
{
	return true;
}