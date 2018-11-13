#include "ModuleEntities.h"
#include "Entity.h"
#include "Player.h"
#include "BlackBandit.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Audio.h"
#include "j1App.h"

ModuleEntities::ModuleEntities() 
{
	name.create("entities");
}

ModuleEntities::~ModuleEntities() {}

bool ModuleEntities::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

bool ModuleEntities::Start() 
{
	return true;
}

bool ModuleEntities::PreUpdate()
{
	/*p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
		
	{
		if (layer->data->data[i] == 336)
		{
			iPoint coords = App->map->TileToWorld(i);
			Entity* entity = new BlackBandit(coords.x, coords.y, ENTITY_TYPE::BLACKBANDIT);
			entities.add(entity);
		}
	}*/
	//p2List_item<Entity*>* item = entities.start;
	//while (item != nullptr)
	//{
	//	//item->data->~Entity();
	//	//entities.del(item);
	//	item = item->next;

	//}
	return true;
}

bool ModuleEntities::Update(float dt)
{
	for (int i = 0; i < entities.count(); ++i)
	{
		if (entities.At(i) != nullptr)
		{
			entities.At(i)->data->Update(dt);
		}
	}
	for (int i = 0; i < entities.count(); ++i)
	{
		if (entities.At(i) != nullptr)
		{
			entities.At(i)->data->Draw();
		}	
	}
	return true;
}

bool ModuleEntities::CleanUp()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		delete item->data;
		entities.del(item);
		item = item->next;

	}
	return true;
}

bool ModuleEntities::SpawnEntity(int x, int y, ENTITY_TYPE type)
{
	bool ret = false;

	switch (type)
	{
	case PLAYER:
	{
		player = new Player(x, y, PLAYER);
		entities.add(player);
		ret = true;
		break;
	}

	case BLACKBANDIT:
	{
		entity = new BlackBandit(x, y, BLACKBANDIT);
		entities.add(entity);
		ret = true;
		break;
	}

	default:
	{ 
		break;
	}
		
	}

	return ret;
}

Player* ModuleEntities::GetPlayer() const
{
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities.At(i) != nullptr)
		{
			if (entities.At(i)->data->type == PLAYER)
			{
				return (Player*)entities.At(i);
			}
		}
	}
	return nullptr;
}