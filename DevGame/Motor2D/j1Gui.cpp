#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Image.h"
#include "Label.h"
#include "Button.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::Update(float dt)
{
	for (int i = 0; i < UI_elements.count(); ++i)
	{
		if (UI_elements.At(i) != nullptr)
		{
			UI_elements.At(i)->data->Draw();
		}
	}
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UI_Element*>* item = UI_elements.start;
	while (item != nullptr)
	{
		delete item->data;
		UI_elements.del(item);
		item = item->next;
	}

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

UI_Element* j1Gui::AddImage(int x, int y, SDL_Rect rect, UI_Element* parent, j1Module* CallBack)
{
	Image* image = new Image(x, y, rect, parent);

	UI_elements.add(image);

	return image;
}

UI_Element* j1Gui::AddButton(int x, int y, SDL_Rect rect, UI_Element* parent, j1Module* CallBack)
{
	Button* button = new Button(x, y, parent);

	UI_elements.add(button);

	return button;
}

UI_Element* j1Gui::AddLabel(int x, int y, UI_Element* parent, j1Module* CallBack)
{
	Label* label = new Label(x, y, parent);

	UI_elements.add(label);

	return label;
}

// class Gui ---------------------------------------------------

