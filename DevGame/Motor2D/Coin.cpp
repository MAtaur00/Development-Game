#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Coin.h"
#include "j1Window.h"
#include "ModuleEntities.h"
#include "j1Scene.h"
#include "Player.h"
#include "ModulePathfindingWalker.h"
#include "j1Audio.h"

Coin::Coin(int x, int y, ENTITY_TYPE type) : Entity(x, y, type)
{
	pos.x = x;
	pos.y = y;
	spawn.x = x;
	spawn.y = y;
	spawnPos = App->map->WorldToMap(x, y);
	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntities(config_file);
	node = &node->child("enemies").child("coin");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "coinRot")
			LoadAnimation(animations, &coinRot);

		animation = &coinRot;
	}
	coinData.jumpSpeed = 0.0f;
	coinData.speed = 0.0f;
	coinData.gravity = 50.0f;
	Start();
}

Coin::~Coin() { CleanUp(); }

bool Coin::Start()
{
	LoadTexture();
	App->entities->player->coin_counter;
	return true;
}

bool Coin::Update(float dt)
{
	animation = &coinRot;
	fPoint tempPos = pos;

	playerPosition = App->entities->player->pos;
	coinPos = App->map->WorldToMap(pos.x, pos.y);
	playerPos = App->map->WorldToMap(playerPosition.x, playerPosition.y);

	if (coinPos.y == playerPos.y && (coinPos.x == playerPos.x + App->entities->player->animation->GetCurrentFrame().w || coinPos.x == playerPos.x) && !App->entities->player->god_mode)
	{
		to_destroy = true;
		App->entities->player->coin_counter++;
		
	}
	
	return true;
}

bool Coin::CleanUp()
{
	App->tex->UnLoad(texture);
	animation = nullptr;
	texture = nullptr;
	return true;
}

bool Coin::Load(pugi::xml_node& data)
{
	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool Coin::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;
}

void Coin::LoadTexture()
{
	texture = App->tex->Load("textures/Enemies/coin_spritesheet.png");
}

void Coin::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	for (pugi::xml_node frame = animation_node.child("frame"); frame; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
	animation->offset_x = animation_node.attribute("offset_x").as_int();
	animation->offset_y = animation_node.attribute("offset_y").as_int();
}