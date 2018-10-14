#include "j1App.h"
#include "ModulePlayer.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Audio.h"


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
	running_right.speed = 0.1f;
	running_right.loop = true;

	//running left animation
	running_left.PushBack({ 275, 1027, 25, 28 });
	running_left.PushBack({ 225, 1027, 25, 28 });
	running_left.PushBack({ 175, 1027, 25, 28 });
	running_left.PushBack({ 126, 1027, 25, 28 });
	running_left.PushBack({ 76, 1027, 25, 28 });
	running_left.PushBack({ 25, 1027, 25, 28 });
	running_left.speed = 0.1f;
	running_left.loop = true;

	//die right animation
	
	die_right.PushBack({ 33,334,19,24 });
	die_right.PushBack({ 81,345,19,24 });
	die_right.PushBack({ 132,345,22,24 });
	die_right.PushBack({ 184,345,18,24 });
	die_right.PushBack({ 237,345,15,24 });
	die_right.PushBack({ 284,345,18,24 });
	die_right.speed = 0.1f;
	die_right.loop = false;


	//die left animation

	die_left.PushBack({ 330,1327,19,24 });
	die_left.PushBack({ 282,1326,19,24 });
	die_left.PushBack({ 249,1327,22,24 });
	die_left.PushBack({ 180,1327,18,24 });
	die_left.PushBack({ 130,1327,15,24 });
	die_left.PushBack({ 80,1327,18,24 });
	die_left.speed = 0.1f;
	die_left.loop = false;


	//slide right animation

	slide_right.PushBack({ 171,130,34,17 });
	slide_right.PushBack({ 221,130,34,17 });
	slide_right.PushBack({ 271,130,34,17 });
	slide_right.PushBack({ 325,130,30,17 });
	slide_right.speed = 0.01f;
	slide_right.loop = true;

	//slide left animation

	slide_left.PushBack({ 177,1112,34,17 });
	slide_left.PushBack({ 127,1112,34,17 });
	slide_left.PushBack({  77,1112,34,17 });
	slide_left.PushBack({  27,1112,30,17 });
	slide_left.speed = 0.1f;
	slide_left.loop = true;

	//fall right animation
	
	fall_right.PushBack({ 84,112,17,31 });
	fall_right.PushBack({ 134,112,17,31 });
	fall_right.speed = 0.1f;
	fall_right.loop = true;

	//fall left animation

	fall_left.PushBack({ 281,1094,17,31 });
	fall_left.PushBack({ 231,1094,17,31 });
	fall_left.speed = 0.1f;
	fall_left.loop = true;


	//jumping left animation
	jumping_left.PushBack({ 331, 1061, 20, 27 });
	jumping_left.PushBack({ 281, 1061, 20, 27 });
	jumping_left.PushBack({ 230, 1061, 19, 27 });
	jumping_left.PushBack({ 181, 1061, 21, 27 });
	jumping_left.PushBack({ 133, 1061, 15, 27 });
	jumping_left.PushBack({  78, 1061, 24, 27 });
	jumping_left.PushBack({  28, 1061, 18, 27 });
	jumping_left.PushBack({ 329, 1106, 26, 27 });
	jumping_left.speed = 0.2f;
	jumping_left.loop = false;

	//jumping right animation
	jumping_right.PushBack({ 31, 79, 20, 27 });
	jumping_right.PushBack({ 81, 79, 20, 27 });
	jumping_right.PushBack({ 133, 79, 19, 27 });
	jumping_right.PushBack({ 180, 79, 21, 27 });
	jumping_right.PushBack({ 234, 79, 15, 27 });
	jumping_right.PushBack({ 280, 79, 24, 27 });
	jumping_right.PushBack({ 336, 79, 18, 27 });
	jumping_right.PushBack({ 27, 124, 26, 27 });
	jumping_right.speed = 0.2f;
	jumping_right.loop = false;

	//wall slide right animation
	wall_slide_right.PushBack({ 182, 409, 17, 32 });
	wall_slide_right.PushBack({ 132, 409, 17, 32 });

	//wall slide left animation
	wall_slide_left.PushBack({ 183, 1391, 17, 32 });
	wall_slide_left.PushBack({ 233, 1391, 17, 32 });


}
ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start()
{
	LoadTexture();

	FindPlayerSpawn();
	SpawnPLayer();
	is_jumping = false;
	looking_right = true;
	return true;
}

bool ModulePlayer::Update(float dt)
{
	if (looking_right)
		animation = &idle_right;
	else if (looking_left)
		animation = &idle_left;

	float falling_speed = playerData.gravity;
	if (can_jump)
		falling_speed -= 1.5;

	fPoint tempPos = playerData.pos;

	tempPos.y += falling_speed;
	
	// numbers in CheckCollision calls are there to avoid the character from levitating in a border (collision looks cleaner)
	if (god_mode == false)
	{
		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& is_jumping == false)
		{
			can_jump = false;
			is_falling = true;
			playerData.pos = tempPos;
			if (looking_left && can_jump == false)
				animation = &fall_left;
			else if (looking_right && can_jump == false)
				animation = &fall_right;
		}
		else
		{
			is_falling = false;
			can_jump = true;
		}

		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH)
		{
			SpawnPLayer();
		}


		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			tempPos = playerData.pos;

			tempPos.x += playerData.speed;

			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				playerData.pos.x = tempPos.x;
				if (is_falling == false)
					animation = &running_right;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::GROUND
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::GROUND
				&& is_falling)
			{
				animation = &wall_slide_right;
				can_jump = true;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(); //with number 0, LoadScene 
			}
			
			looking_left = false;
			looking_right = true;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			tempPos = playerData.pos;

			tempPos.x -= playerData.speed;
			if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				if (tempPos.x >= App->render->camera.x)
					playerData.pos.x = tempPos.x;
				if (is_falling == false)
					animation = &running_left;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::GROUND
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::GROUND
				&& is_falling)
			{
				animation = &wall_slide_left;
				can_jump = true;
			}
			looking_left = true;
			looking_right = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && is_jumping == false && can_jump)
		{
			can_jump = false;
			jumping_left.Reset();
			jumping_right.Reset();
			is_jumping = true;
			cont = 0;
		}
		if (is_jumping)
		{
			tempPos = playerData.pos;

			tempPos.y -= playerData.jumpSpeed;
			if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y })) == COLLISION_TYPE::AIR)
			{
				if (tempPos.y >= App->render->camera.y)
					playerData.pos.y = tempPos.y;
				if (looking_left)
					animation = &jumping_left;
				else if (looking_right)
					animation = &jumping_right;
			}
			if (cont == 35)
			{
				is_jumping = false;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT)
		{
			tempPos = playerData.pos;

			tempPos.x += playerData.speed;

			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				playerData.pos.x = tempPos.x;
				animation = &slide_right;
			}

			looking_left = false;
			looking_right = true;
		}

	}
	else 
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			playerData.pos.y -= 4;
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			playerData.pos.y += 4;
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			playerData.pos.x += 4;
			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(3); //with number 3 LoadScene loads the next map
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			playerData.pos.x -= 4;
	}
	App->render->Blit(texture, playerData.pos.x, playerData.pos.y, &animation->GetCurrentFrame());
	cont++;
	return true;
}

bool ModulePlayer::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}

bool ModulePlayer::Load(pugi::xml_node& data)
{
	playerData.pos.x = data.child("position").attribute("x").as_float();
	playerData.pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool ModulePlayer::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)playerData.pos.x;
	position.append_attribute("y") = (float)playerData.pos.y;

	return true;
}

void ModulePlayer::LoadTexture()
{
	texture = App->tex->Load("textures/Player/player_spritesheet.png");
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

	case 34:
		return COLLISION_TYPE::WIN;
		break;
	}	

	return COLLISION_TYPE::AIR;
}

void ModulePlayer::FindPlayerSpawn()
{
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 27)
		{
			spawn = App->map->TileToWorld(i);
		}
	}
}

void ModulePlayer::SpawnPLayer()
{
	playerData.pos.x = spawn.x;
	playerData.pos.y = spawn.y;
	App->render->camera.x = 0;
}