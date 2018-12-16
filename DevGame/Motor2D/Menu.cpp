#include "Menu.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "j1Scene.h"
#include "Settings.h"
#include "ModuleEntities.h"
#include "InGameMenu.h"
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
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 1024, 640 }, NULL, this);

	title = (Button*)App->gui->AddButton(310, 100, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, "UNDERGROUND HERO", NULL, this);

	button_continue = (Button*)App->gui->AddButton(200, 350, { 1298, 70, 246, 61 }, { 1298, 326, 246, 61 }, { 1298, 189, 246, 61 }, "Continue", NULL, this);
	button_new_game = (Button*)App->gui->AddButton(550, 350, { 1298, 70, 246, 61 }, { 1298, 326, 246, 61 }, { 1298, 189, 246, 61 }, "New Game", NULL, this);
	button_settings = (Button*)App->gui->AddButton(200, 500, { 1298, 70, 246, 61 }, { 1298, 326, 246, 61 }, { 1298, 189, 246, 61 }, "Settings", NULL, this);
	button_exit = (Button*)App->gui->AddButton(550, 500, { 1595, 71, 246, 59 }, { 1595, 327, 246, 59 }, { 1595, 190, 246, 59 }, "Exit", NULL, this);

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

void Menu::CallBack(UI_Element* element)
{
	if (element == button_continue)
	{
		if (App->inGameMenu->saved)
		{
			active = false;
			App->scene->active = true;
			App->entities->active = true;
			CleanUp();
			App->scene->Start();
			App->entities->Start();
			App->scene->loadScene = true;
		}
	}
	else if (element == button_new_game)
	{
		active = false;
		App->scene->active = true;
		App->entities->active = true;
		CleanUp();
		App->scene->Start();
		App->entities->Start();
	}
	else if (element == button_settings)
	{
		active = false;
		App->settings->active = true;
		CleanUp();
		App->settings->Start();
	}
	else if (element == button_exit)
	{
		exit = true;
	}
}

bool Menu::PostUpdate()
{
	return !exit;
}

bool Menu::CleanUp()
{
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(bg_image)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_continue->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_continue)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_new_game->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_new_game)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_settings->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_settings)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_exit->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_exit)));

	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(title->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(title)));

	delete bg_image;
	delete button_continue;
	delete button_new_game;
	delete button_settings;
	delete button_exit;
	delete title;

	return true;
}