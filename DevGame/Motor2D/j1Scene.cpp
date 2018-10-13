#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	for (pugi::xml_node map_node = config.child("maps"); map_node != nullptr; map_node = map_node.next_sibling("maps")) 
	{

		const char* name = map_node.attribute("map").as_string();

		MapsList_String.add(name);
	}

	CurrentMap = MapsList_String.start;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load(CurrentMap->data);
	App->audio->PlayMusic("audio/music/Mushroom_Theme.ogg");
	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		LoadScene(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		LoadScene();

	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame("save_game.xml");
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		App->LoadGame("save_game.xml");
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		App->map->draw_logic = !App->map->draw_logic;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		App->player->god_mode = !App->player->god_mode;
	}

	int camera_speed = 2;

	if (App->player->god_mode)
		camera_speed = 4;

	if (App->player->playerData.pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 2)) >= 0) 
	{
		if (App->render->camera.x - App->render->camera.w > -(App->map->data.width*App->map->data.tile_width))
			App->render->camera.x -= camera_speed;
	}

	if (App->player->playerData.pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 2)) <= 0) 
	{
		if (App->render->camera.x < 0)
			App->render->camera.x += camera_speed;
	}
	



	//FadeToBlack

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->map, App->map,1.5f);
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();


	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count());

	App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	return true;
}

bool j1Scene::LoadScene(int map) 
{
	App->map->CleanUp();
	App->tex->FreeTextures();
	App->player->LoadTexture();

	if (map == 3) {

		if (CurrentMap->next != nullptr)
			CurrentMap = CurrentMap->next;
		else
			CurrentMap = MapsList_String.start;
	}
	else if (map != -1) 
	{
		CurrentMap = MapsList_String.start;
		for (int i = 1; i < map; i++) {
			if (CurrentMap->next != nullptr)
				CurrentMap = CurrentMap->next;

			else
				break;
		}

	}
	App->map->Load(CurrentMap->data);
	App->player->FindPlayerSpawn();
	App->player->SpawnPLayer();

	return true;
}

// Load
bool j1Scene::Load(pugi::xml_node&  savegame) {
	currmap = savegame.child("Map").attribute("CurrentMap").as_int();

	App->map->CleanUp();

	switch (currmap)
	{
	case 1:
		App->map->Load("Map1.tmx");
		break;
	case 2:
		App->map->Load("Map2.tmx");
		break;
	default:
		break;
	}
	return true;
}

//Save
bool j1Scene::Save(pugi::xml_node& data) const {

	pugi::xml_node cam = data.append_child("Map");

	cam.append_attribute("CurrentMap") = currmap;
	return true;
}