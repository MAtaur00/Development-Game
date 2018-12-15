#include "Settings.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "Brofiler/Brofiler.h"

Settings::Settings()
{
	name.create("credits");
}

Settings::~Settings() {}

bool Settings::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

bool Settings::Start()
{
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 640, 480 }, NULL, this);

	vsync_checkbox = (CheckBox*)App->gui->AddCheckbox(0, 0, { 1117, 537, 27, 27 }, NULL, this);

	//volume_slider = (ScrollBar*)App->gui->AddScrollbar(0, 0, {}, NULL, this);

	button_credits = (Button*)App->gui->AddButton(0, 0, { 998, 45, 246, 61 }, NULL, this);

	return true;
}

bool Settings::PreUpdate()
{
	return true;
}