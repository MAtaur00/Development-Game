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
	p2List_item<Entity*>* item;
	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data->to_destroy)
		{
		//	item->data->~Entity();
			entities.del(item);
		}
	}
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
	p2List_item<Entity*>* item;
	for (item = entities.start; item != NULL; item = item->next)
	{
		//item->data->~Entity();
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
	{
		player = new Player(x, y, PLAYER);
		entities.add(player);
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