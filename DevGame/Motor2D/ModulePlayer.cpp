#include "j1App.h"
#include "ModulePlayer.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Scene.h"


ModulePlayer::ModulePlayer()
{
	name.create("player");

	//idle right animation
	idle_right.PushBack({ 29, 6, 21, 30 });
	idle_right.PushBack({ 79, 6, 21, 30 });
	idle_right.PushBack({ 129, 6, 21, 30 });
	idle_right.PushBack({ 179, 6, 21, 30 });
	idle_right.speed = 0.05f;
	idle_right.loop = true;

	//idle left animation
	idle_left.PushBack({ 332, 988, 21, 30 });
	idle_left.PushBack({ 282, 988, 21, 30 });
	idle_left.PushBack({ 232, 988, 21, 30 });
	idle_left.PushBack({ 182, 988, 21, 30 });
	idle_left.speed = 0.05f;
	idle_left.loop = true;

	//running right animation
	running_right.PushBack({ 82, 45, 25, 28 });
	running_right.PushBack({ 132, 45, 25, 28 });
	running_right.PushBack({ 182, 45, 25, 28 });
	running_right.PushBack({ 231, 45, 25, 28 });
	running_right.PushBack({ 281, 45, 25, 28 });
	running_right.PushBack({ 332, 45, 25, 28 });
	running_right.speed = 0.05f;
	running_right.loop = true;

	//running left animation
	running_left.PushBack({ 275, 1027, 25, 28 });
	running_left.PushBack({ 225, 1027, 25, 28 });
	running_left.PushBack({ 175, 1027, 25, 28 });
	running_left.PushBack({ 126, 1027, 25, 28 });
	running_left.PushBack({ 76, 1027, 25, 28 });
	running_left.PushBack({ 25, 1027, 25, 28 });
	running_left.speed = 0.05f;
	running_left.loop = true;

	////jumping right animation
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.PushBack({ 17, 126, 36, 38 });
	//jumping_right.speed = 0.05f;
	//jumping_right.loop = false;

	////jumping left animation
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.PushBack({ 405, 121, 35, 38 });
	//jumping_left.speed = 0.05f;
	//jumping_left.loop = false;

}
ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start()
{
	texture = App->tex->Load("textures/Player/player_spritesheet.png");

	playerData.pos = App->map->initial_position;
	looking_right = true;
	return true;
}

bool ModulePlayer::Update(float dt)
{
	if (looking_right)
		animation = &idle_right;
	else if (looking_left)
		animation = &idle_left;
	dt = float(1) / 60;

	fPoint tempPos = playerData.pos;

	tempPos.y += dt * 50;

	if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + playerData.player_height })) == COLLISION_TYPE::AIR 
		&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + playerData.player_height })) == COLLISION_TYPE::AIR)
	{
		playerData.pos = tempPos;
	}

	if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + playerData.player_height })) == COLLISION_TYPE::DEATH
		&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + playerData.player_height })) == COLLISION_TYPE::DEATH)
	{
		playerData.pos = App->map->initial_position;
		App->render->camera.x = 0;
	}


	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		tempPos = playerData.pos;

		tempPos.x += dt * 50;

		if (CheckCollision(GetPlayerTile({ tempPos.x + playerData.player_width, tempPos.y })) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x + playerData.player_width, tempPos.y + playerData.player_height })) == COLLISION_TYPE::AIR)
		{
			playerData.pos.x += dt * 50;
			animation = &running_right;
		}	

		looking_left = false;
		looking_right = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		tempPos = playerData.pos;

		tempPos.x -= dt * 50;

		if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + playerData.player_height })) == COLLISION_TYPE::AIR)
		{
			playerData.pos.x -= dt * 50;
			animation = &running_left;
		}

		looking_left = true;
		looking_right = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		tempPos = playerData.pos;

		tempPos.y -= dt * 100;

		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y})) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y})) == COLLISION_TYPE::AIR)
		{
			playerData.pos.y -= dt * 100;
			if (looking_left)
				animation = &running_left;
			else if (looking_right)
				animation = &running_right;
		}
	}

	App->render->Blit(texture, playerData.pos.x, playerData.pos.y, &animation->GetCurrentFrame());

	return true;
}

bool ModulePlayer::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}

bool ModulePlayer::Load(pugi::xml_node& data)
{
	playerData.pos.x = data.child("pos").attribute("x").as_float();
	playerData.pos.y = data.child("pos").attribute("y").as_float();

	return true;
}

bool ModulePlayer::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("pos");

	position.append_attribute("x") = (float)playerData.pos.x;
	position.append_attribute("y") = (float)playerData.pos.y;

	return true;
}

int ModulePlayer::GetPlayerTile(fPoint pos) const
{
	iPoint position = App->map->WorldToMap(pos.x, pos.y);

	int tile_number = position.y * App->map->data.width + position.x;

	return tile_number;
}

COLLISION_TYPE ModulePlayer::CheckCollision(int x) const
{
	p2List_item<MapLayer*>* layer_colliders = App->map->data.layers.end;
	
	switch (layer_colliders->data->data[x])
	{
	default:
		break;

	case 25:
		return COLLISION_TYPE::GROUND;
		break;

	case 26:
		return COLLISION_TYPE::DEATH;
		break;
	}
	

	return COLLISION_TYPE::AIR;
}