#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "BlackBandit.h"
#include "j1Window.h"
#include "ModuleEntities.h"
#include "j1Scene.h"
#include "Player.h"
#include "ModulePathfindingWalker.h"
#include "j1Audio.h"

BlackBandit::BlackBandit(int x, int y, ENTITY_TYPE type) : Entity(x, y, type)
{
	pos.x = x;
	pos.y = y;
	spawn.x = x;
	spawn.y = y;
	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntities(config_file);
	node = &node->child("enemies").child("blackBandit");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "idle")
			LoadAnimation(animations, &idle);
		else if (tmp == "idleSwordUp")
			LoadAnimation(animations, &idleSwordUp);
		else if (tmp == "running")
			LoadAnimation(animations, &running);
		else if (tmp == "attack")
			LoadAnimation(animations, &attack);
		else if (tmp == "death")
			LoadAnimation(animations, &death);
		else if (tmp == "falling")
			LoadAnimation(animations, &falling);

		animation = &idle;
	}
	banditData.jumpSpeed = 0.0f;
	banditData.speed = 0.0f;
	banditData.gravity = 50.0f;
	Start();
}

BlackBandit::~BlackBandit() { CleanUp(); }

bool BlackBandit::Start()
{
	LoadTexture();
	path_texture = App->tex->Load("textures/cross_texture.png");
	return true;
}

bool BlackBandit::Update(float dt)
{
	banditData.jumpSpeed = 0.0f;
	banditData.speed = 0.0f;
	animation = &idle;
	fPoint tempPos = pos;

	// GRAVITY
	tempPos.y += banditData.gravity * dt;
	if (CheckCollision(GetEntityTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
		&& CheckCollision(GetEntityTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
	{
		pos = tempPos;
		animation = &falling;
	}

	playerPosition = App->entities->player->pos;
	banditPos = App->map->WorldToMap(pos.x, pos.y);
	playerPos = App->map->WorldToMap(playerPosition.x, playerPosition.y);

	if (banditPos.x < playerPos.x + 8 && banditPos.x > playerPos.x - 8 && banditPos.y < playerPos.y + 8 && banditPos.y > playerPos.y - 8)
	{
		if (App->pathfindingWalker->CreatePath(banditPos, playerPos) != -1)
		{
			const p2DynArray<iPoint>* path = App->pathfindingWalker->GetLastPath();

			if (App->map->draw_logic)
			{
				for (uint i = 0; i < path->Count(); ++i)
				{
					iPoint nextPoint = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
					App->render->Blit(path_texture, nextPoint.x, nextPoint.y);
				}
			}
			if (path->Count() > 0)
			{
				iPoint pathPoint = iPoint(path->At(0)->x, path->At(0)->y);
				if (pathPoint.x < banditPos.x)
				{
					animation = &running;
					flip = SDL_RendererFlip::SDL_FLIP_NONE;
					banditData.speed = -70 * dt;
				}
				else if (pathPoint.x > banditPos.x)
				{
					animation = &running;
					flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
					banditData.speed = 70 * dt;
				}
				if (pathPoint.y > banditPos.y)
				{
					animation = &falling;
					banditData.jumpSpeed = 70 * dt;
				}
			}
		}
	}
	pos.x += banditData.speed;
	pos.y += banditData.jumpSpeed;

	if (banditPos.y == playerPos.y && (banditPos.x == playerPos.x + App->entities->player->animation->GetCurrentFrame().w || banditPos.x == playerPos.x) && !App->entities->player->god_mode)
	{
		if (!App->entities->player->playerAttacking)
		{
			App->audio->PlayFx(2);
			App->entities->player->SpawnPLayer();
			pos = spawn;
		}
		else
		{
			animation = &death;
			to_destroy = true;
		}
	}

	return true;
}

bool BlackBandit::CleanUp()
{
	App->tex->UnLoad(texture);
	/*delete &idle;
	delete &idleSwordUp;
	delete &running;
	delete &attack;
	delete &death;*/
	animation = nullptr;
	texture = nullptr;
	return true;
}

bool BlackBandit::Load(pugi::xml_node& data)
{
	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool BlackBandit::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;
}

void BlackBandit::LoadTexture()
{
	texture = App->tex->Load("textures/Enemies/HeavyBandits_spritesheet.png");
}

void BlackBandit::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	for (pugi::xml_node frame = animation_node.child("frame"); frame; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
	animation->offset_x = animation_node.attribute("offset_x").as_int();
	animation->offset_y = animation_node.attribute("offset_y").as_int();
}