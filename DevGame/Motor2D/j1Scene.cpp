#include "p2Defs.h"
#include "j1Gui.h"
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
#include "ModuleEntities.h"
#include "Entity.h"
#include "Player.h"
#include "ModulePathfinding.h"
#include "ModulePathfindingWalker.h"

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

	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data, true))
		App->pathfinding->SetMap(w, h, data);

	int w2, h2;
	uchar* data2 = NULL;
	if (App->map->CreateWalkabilityMap(w2, h2, &data2, false))
		App->pathfindingWalker->SetMap(w2, h2, data2);

	RELEASE_ARRAY(data);
	RELEASE_ARRAY(data2);

	App->audio->PlayMusic("audio/music/Mushroom_Theme.ogg");

	iPoint spawnEntity;
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 204)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, PLAYER);
		}
		if (layer->data->data[i] == 336)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, BLACKBANDIT);
		}
		if (layer->data->data[i] == 269)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, BIGBAT);
		}

		if (layer->data->data[i] == 71)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, COIN);
		}
	}

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
		LoadScene(0);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
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
		App->entities->player->god_mode = !App->entities->player->god_mode;
		App->entities->player->is_falling = true;
		App->entities->player->is_jumping = false;

	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		LOG("1");
		vsyncCont = App->config.child("vsync").append_attribute("value").as_bool();
		vsyncCont =true;
	
	}

	float camera_speed = 125.0f;

	if (App->entities->player->god_mode)
		camera_speed = 300.0f;

	if (App->entities->player->pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 2)) >= 0)
	{
		if (App->render->camera.x - App->render->camera.w > -(App->map->data.width*App->map->data.tile_width))
			App->render->camera.x -= camera_speed * dt;
	}

	if (App->entities->player->pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 3)) <= 0)
	{
		if (App->render->camera.x < 0)
			App->render->camera.x += camera_speed * dt;
	}
	
	//App->render->Blit(img, 0, 0);
	App->map->Draw();

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
	App->entities->player->to_destroy = true;
	LOG("Freeing scene");
	return true;
}

bool j1Scene::LoadScene(int map) 
{
	App->map->CleanUp();
	App->tex->FreeTextures();
	/*App->entities->player->LoadTexture();*/
	
	p2List_item<Entity*>* item = App->entities->entities.start;
	while (item != nullptr)
	{
		delete item->data;
		App->entities->entities.del(item);
		item = item->next;
	}
	if (map == -1) {

		if (CurrentMap->next != nullptr)
		{
			CurrentMap = CurrentMap->next;
			currmap++;
		}
		else
		{
			CurrentMap = MapsList_String.start;
			currmap = 1;
		}
	}
	else if (map > 0) 
	{
		CurrentMap = MapsList_String.start;
		for (int i = 1; i < map; i++) {
			if (CurrentMap->next != nullptr)
			{
				CurrentMap = CurrentMap->next;
				currmap = map;
			}
			else
				break;
		}

	}
	App->map->Load(CurrentMap->data);
	iPoint spawnEntity;
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 204)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, PLAYER);
		}
		if (layer->data->data[i] == 336)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, BLACKBANDIT);
		}
		if (layer->data->data[i] == 269)
		{
			spawnEntity = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnEntity.x, spawnEntity.y, BIGBAT);
		}
	}
	/*App->entities->player->FindPlayerSpawn();
	App->entities->player->SpawnPLayer();*/

	return true;
}

// Load
bool j1Scene::Load(pugi::xml_node&  savegame) {
	currmap = savegame.child("Map").attribute("CurrentMap").as_int();	

	App->map->CleanUp();

	switch (currmap)
	{
	case 1:
		App->map->Load("level1_WithLayers.tmx");
		break;
	case 2:
		App->map->Load("level2_WithLayers.tmx");
		break;
	default:
		break;
	}

	App->entities->player->Load(savegame);
	return true;
}

//Save
bool j1Scene::Save(pugi::xml_node& data) const 
{
	pugi::xml_node map = data.append_child("Map");

	App->entities->player->Save(data);

	map.append_attribute("CurrentMap") = currmap;
	return true;
}