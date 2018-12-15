#include "Credits.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "Brofiler/Brofiler.h"

Credits::Credits()
{
	name.create("credits");
}

Credits::~Credits() {}

bool Credits::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

bool Credits::Start()
{
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 640, 480 }, NULL, this);

	credits_label = (Label*)App->gui->AddLabel(0, 0, NULL, this);

	return true;
}

bool Credits::PreUpdate()
{
	return true;
}