#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "Skeleton.h"
#include "j1Window.h"
#include "ModuleEntities.h"
#include "j1Scene.h"

Skeleton::Skeleton(int x, int y, ENTITY_TYPE type) : Entity(x, y, type)
{
	pos.x = x;
	pos.y = y;
	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntities(config_file);
	node = &node->child("enemies").child("skeleton");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "idle")
			LoadAnimation(animations, &idle);
		else if (tmp == "notice")
			LoadAnimation(animations, &notice);
		else if (tmp == "hit")
			LoadAnimation(animations, &hit);
		else if (tmp == "walk")
			LoadAnimation(animations, &walk);
		else if (tmp == "death")
			LoadAnimation(animations, &death);

		animation = &idle;
	}
	Start();
}

Skeleton::~Skeleton() { CleanUp(); }

bool Skeleton::Start()
{
	LoadTexture();
	return true;
}

bool Skeleton::Update(float dt)
{
	animation = &idle;
	fPoint tempPos = pos;

	// GRAVITY
	tempPos.y += skeletonData.gravity;
	if (CheckCollision(GetEntityTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
		&& CheckCollision(GetEntityTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
	{
		pos = tempPos;
	}
	return true;
}

bool Skeleton::CleanUp()
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

bool Skeleton::Load(pugi::xml_node& data)
{
	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool Skeleton::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;
}

void Skeleton::LoadTexture()
{
	texture = App->tex->Load("textures/Enemies/skeleton_spritesheet.png");
}

void Skeleton::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	for (pugi::xml_node frame = animation_node.child("frame"); frame; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
	animation->offset_x = animation_node.attribute("offset_x").as_int();
	animation->offset_y = animation_node.attribute("offset_y").as_int();
}