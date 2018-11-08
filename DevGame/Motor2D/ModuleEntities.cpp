#include "ModuleEntities.h"
#include "Entity.h"
#include "Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Audio.h"

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
	for (p2List_item<Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		if (item->data->to_destroy)
		{
			delete(item);
			entities.del(item);
		}
	}
	return true;
}

bool ModuleEntities::Update(float dt)
{
	for (int i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Update(dt);
		}
	}
	for (int i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Draw();
		}	
	}
	return true;
}

bool ModuleEntities::CleanUp()
{
	for (p2List_item<Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		delete(item);
		entities.del(item);
	}
	return true;
}

bool ModuleEntities::SpawnEntity(int x, int y, ENTITY_TYPE type)
{
	bool ret = false;

	switch (type)
	{
	case ENTITY_TYPE::PLAYER:
		Player* player = new Player(x, y, PLAYER);
		entities.add(player);
		break;

	default:
		break;
	}

	return ret;
}

Player* ModuleEntities::GetPlayer() const
{
	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->type == PLAYER)
			{
				return (Player*)entities[i];
			}
		}
	}
	return nullptr;
}