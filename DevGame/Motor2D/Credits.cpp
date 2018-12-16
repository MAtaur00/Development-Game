#include "Credits.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1App.h"
#include "Settings.h"
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
	bg_image = (Image*)App->gui->AddImage(0, 0, { 0, 0, 1024, 640 }, NULL, this);

	button_credits_back = (Button*)App->gui->AddButton(550, 500, { 1595, 71, 246, 59 }, { 1595, 327, 246, 59 }, { 1595, 190, 246, 59 }, "Back", NULL, this);

	credits_label = (Label*)App->gui->AddLabel(0, 0, NULL, this);

	return true;
}

bool Credits::PreUpdate()
{
	return true;
}

bool Credits::Update(float dt)
{
	return true;
}

void Credits::CallBack(UI_Element* element)
{
	if (element == button_credits_back)
	{
		active = false;
		App->settings->active = true;
		CleanUp();
		App->settings->Start();

	}
}

bool Credits::PostUpdate()
{
	return true;
}

bool Credits::CleanUp()
{
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(bg_image)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_credits_back->text)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(button_credits_back)));

	delete bg_image;
	delete button_credits_back;

	return true;
}