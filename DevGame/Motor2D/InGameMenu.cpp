#include "InGameMenu.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "j1Scene.h"
#include "Menu.h"
#include "ModuleEntities.h"
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
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 1024, 640 }, NULL, this);

	button_resume = (Button*)App->gui->AddButton(200, 500, { 1298, 70, 246, 61 }, { 1298, 326, 246, 61 }, { 998, 189, 246, 61 }, "Resume", NULL, this);
	button_main_menu = (Button*)App->gui->AddButton(550, 500, { 1595, 71, 246, 59 }, { 1595, 327, 246, 59 }, { 1595, 190, 246, 59 }, "Main Menu", NULL, this);

	//volume = (ScrollBar*)App->gui->AddScrollbar(0, 0, { 1393, 521, 246, 41 }, { 1663, 514, 52, 48 }, NULL, this);

	return true;
}

bool InGameMenu::PreUpdate()
{
	return true;
}

bool InGameMenu::Update(float dt)
{
	return true;
}

void InGameMenu::CallBack(UI_Element* element)
{
	if (element == button_resume)
	{
		active = false;
		CleanUp();
	}
	else if (element == button_main_menu)
	{
		active = false;
		App->menu->active = true;
		CleanUp();
		App->menu->Start();
	}
}

bool InGameMenu::PostUpdate()
{
	return true;
}

bool InGameMenu::CleanUp()
{
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(bg_image)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_resume->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_resume)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_main_menu->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_main_menu)));

	delete bg_image;
	delete button_resume;
	delete button_main_menu;

	return true;
}