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
#include "CheckBox.h"
#include "Scrollbar.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& config)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = config.child("atlas").attribute("file").as_string("");

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
			UI_elements.At(i)->data->Update(dt);
			UI_elements.At(i)->data->Draw();
		}
	}

	return true;
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
	Image* image = new Image(x, y, rect, parent, CallBack);

	UI_elements.add(image);

	return image;
}

UI_Element* j1Gui::AddButton(int x, int y, SDL_Rect idle, SDL_Rect hover, SDL_Rect click, char* name, UI_Element* parent, j1Module* CallBack)
{
	Label* text = new Label(x + 70, y + 15, NULL, CallBack);
	Button* button = new Button(x, y, idle, hover, click, parent, text, CallBack);

	text->parent = button;
	
	text->SetText(name);

	UI_elements.add(button);
	UI_elements.add(text);

	return button;
}

UI_Element* j1Gui::AddLabel(int x, int y, UI_Element* parent, j1Module* CallBack)
{
	Label* label = new Label(x, y, parent, CallBack);

	UI_elements.add(label);

	return label;
}

UI_Element* j1Gui::AddCheckbox(int x, int y, SDL_Rect rect, UI_Element* parent, j1Module* CallBack)
{
	CheckBox* checkBox = new CheckBox(x, y, parent, CallBack);

	UI_elements.add(checkBox);

	return checkBox;
}

//UI_Element* j1Gui::AddScrollbar(int x, int y, SDL_Rect rect, SDL_Rect slider, UI_Element* parent, j1Module* CallBack)
//{
//	ScrollBar* volume_scrollbar = new ScrollBar(x, y, parent);
//
//	UI_elements.add(volume_scrollbar);
//
//	return volume_scrollbar;
//}

// class Gui ---------------------------------------------------

