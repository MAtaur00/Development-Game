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
#include "Coin.h"
#include "Entity.h"
#include "Player.h"
#include "InGameMenu.h"
#include "ModulePathfinding.h"
#include "Menu.h"
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

	first_load = false;

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

	coins_collected = 0;
	ui_coin = (Image*)App->gui->AddImage(400, 20, { 1459, 488, 32, 32 }, NULL, this);

	game_time_label = (Label*)App->gui->AddLabel(20, 20, NULL, this);
	static char score_timer[6];
	sprintf_s(score_timer, 6, "%02i:%02i", 0, 0);
	game_time_label->SetText(score_timer);

	coin_score = (Label*)App->gui->AddLabel(450, 20, NULL, this);
	static char score_coins[6];
	sprintf_s(score_coins, 6, "%c %i", 'x', coins_collected);
	coin_score->SetText(score_coins);

	game_time.Start();
	timer_pause = 0u;

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
	if (!pause) {

		static char score_timer[6];
		timer_game = start_time + ((uint)game_time.ReadSec() - timer_pause);
		sprintf_s(score_timer, 6, "%02i:%02i", timer_game / 60, timer_game % 60);
		game_time_label->SetText(score_timer);

		static char score_coins[6];
		coins_collected = App->entities->player->coin_counter;
		sprintf_s(score_coins, 6, "%c %i", 'x', coins_collected);
		coin_score->SetText(score_coins);

		if (lives >= 1)
			life1 = (Image*)App->gui->AddImage(800, 20, { 1565, 489, 36, 32 }, NULL, this);

		if (lives >= 2)
			life2 = (Image*)App->gui->AddImage(850, 20, { 1565, 489, 36, 32 }, NULL, this);

		if (lives >= 3)
			life3 = (Image*)App->gui->AddImage(900, 20, { 1565, 489, 36, 32 }, NULL, this);
	}


	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		LoadScene(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		LoadScene(0);
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame("save_game.xml");
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN || loadScene) {
		loadScene = false;
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
		vsyncCont = !vsyncCont;
	
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

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		pause = true;
		pause_time.Start();
		App->inGameMenu->active = true;
		App->inGameMenu->Start();
	}

	if (lives <= 0)
	{
		active = false;
		App->entities->active = false;
		App->menu->active = true;
		CleanUp();
		//App->entities->CleanUp();
		App->menu->Start();
	}

	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(life1)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(life2)));
	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(life3)));

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	if (App->entities->player)
		App->entities->player->to_destroy = true;

	//game_time_label->~Label();

	App->gui->UI_elements.del(App->gui->UI_elements.At(App->gui->UI_elements.find(ui_coin)));

	delete ui_coin;
	delete life1;
	delete life2;
	delete life3;
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
	App->gui->Start();
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
	ui_coin = (Image*)App->gui->AddImage(400, 20, { 1459, 488, 32, 32 }, NULL, this);

	if (lives >= 1)
		life1 = (Image*)App->gui->AddImage(800, 20, { 1565, 489, 36, 32 }, NULL, this);

	if (lives >= 2)
		life2 = (Image*)App->gui->AddImage(850, 20, { 1565, 489, 36, 32 }, NULL, this);

	if (lives >= 3)
		life3 = (Image*)App->gui->AddImage(900, 20, { 1565, 489, 36, 32 }, NULL, this);

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

	start_time = savegame.child("timer").attribute("time").as_int();

	App->entities->player->Load(savegame);
	return true;
}

//Save
bool j1Scene::Save(pugi::xml_node& data) const 
{
	pugi::xml_node map = data.append_child("Map");
	pugi::xml_node timer = data.append_child("timer");

	App->entities->player->Save(data);

	map.append_attribute("CurrentMap") = currmap;

	timer.append_attribute("time") = timer_game;

	return true;
}