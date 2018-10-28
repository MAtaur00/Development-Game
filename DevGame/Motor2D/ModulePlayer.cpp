#include "j1App.h"
#include "ModulePlayer.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Window.h"


ModulePlayer::ModulePlayer()
{
	name.create("player");

	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntities(config_file);
	node = &node->child("player");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "idle")
			LoadAnimation(animations, &idle);
		else if (tmp == "running")
			LoadAnimation(animations, &running);
		else if (tmp == "die")
			LoadAnimation(animations, &die);
		else if (tmp == "slide")
			LoadAnimation(animations, &slide);
		else if (tmp == "fall")
			LoadAnimation(animations, &fall);
		else if (tmp == "jumping")
			LoadAnimation(animations, &jumping);
		else if (tmp == "wall_slide")
			LoadAnimation(animations, &wall_slide);
		else if (tmp == "punch")
			LoadAnimation(animations, &punch);
		else if (tmp == "punch_barrage")
			LoadAnimation(animations, &punch_barrage);
		else if (tmp == "kick")
			LoadAnimation(animations, &kick);
		else if (tmp == "double_kick")
			LoadAnimation(animations, &double_kick);
		else if (tmp == "unsheathe")
			LoadAnimation(animations, &unsheathe);
		else if (tmp == "idle_sword")
			LoadAnimation(animations, &idle_sword);
	}

	/*App->audio->fx.add[1] = App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->fx.add[2] = App->audio->LoadFx("audio/fx/HurtFx.wav");*/
}
ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start()
{
	LoadTexture();
	App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->LoadFx("audio/fx/HurtFx.wav");

	FindPlayerSpawn();
	SpawnPLayer();
	is_jumping = false;
	looking_right = true;
	return true;
}

bool ModulePlayer::Update(float dt)
{
	if (!sword)
		animation = &idle;
	else if (sword)
		animation = &idle_sword;
	if (looking_right)
		flip = SDL_FLIP_NONE;
	else if (looking_left)
		flip = SDL_FLIP_HORIZONTAL;

	float falling_speed = playerData.gravity;
	if (can_jump)
		falling_speed -= 1.5;

	fPoint tempPos = playerData.pos;

	// numbers in CheckCollision calls are there to avoid the character from levitating in a border (collision looks cleaner)
	if (god_mode == false)
	{
		// GRAVITY
		tempPos.y += falling_speed;
		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& is_jumping == false)
		{
			can_jump = false;
			is_falling = true;
			playerData.pos = tempPos;
			if (!can_jump)
				animation = &fall;
		}
		else
		{
			is_falling = false;
			can_jump = true;
		}

		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH)
		{
			App->audio->PlayFx(2);
			SpawnPLayer();
		}
		//--------------------------------

		// MOVEMENT RIGHT
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && !is_punching && !is_kicking)
		{
			looking_left = false;
			looking_right = true;
			tempPos = playerData.pos;

			tempPos.x += playerData.speed;

			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				playerData.pos.x = tempPos.x;
				if (!is_falling)
					animation = &running;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::GROUND
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::GROUND
				&& is_falling)
			{
				animation = &wall_slide;
				can_jump = true;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(); 
			}
		}
		//--------------------------------

		// MOVEMENT LEFT
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && !is_punching && !is_kicking)
		{
			looking_left = true;
			looking_right = false;
			tempPos = playerData.pos;

			tempPos.x -= playerData.speed;
			if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				if (tempPos.x >= App->render->camera.x)
					playerData.pos.x = tempPos.x;
				if (is_falling == false)
					animation = &running;
			}
			else if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::GROUND
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::GROUND
				&& is_falling)
			{
				animation = &wall_slide;
				can_jump = true;
			}
		}
		//--------------------------------

		// JUMP
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && is_jumping == false && can_jump && !is_punching && !is_kicking)
		{
			App->audio->PlayFx(1);
			can_jump = false;
			jumping.Reset();
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
				animation = &jumping;
			}
			if (cont == 35)
			{
				is_jumping = false;
			}
		}
		//--------------------------------

		/*if (App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT)
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
		*/
		/*if (animation->Finished())
		{
			if (offset_x_added)
			{
				playerData.pos.x += animation->offset_x;
				offset_x_added = false;
			}
			if (offset_y_added)
			{
				playerData.pos.y -= animation->offset_y;
				offset_y_added = false;
			}
		}*/
	}
	else 
	{
		// MOVEMENT UP
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			tempPos.y -= 4;
			if (tempPos.y >= App->render->camera.y)
				playerData.pos.y -= 4;
		}
		//--------------------------------

		// MOVEMENT DOWN
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			tempPos.y += 4;
			if (tempPos.y + animation->GetCurrentFrame().h <= App->render->camera.y + App->win->height)
				playerData.pos.y += 4;
		}
		//--------------------------------

		// MOVEMENT RIGHT
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			playerData.pos.x += 4;
			animation = &running;
			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(); //with number 3 LoadScene loads the next map
			}
		}
		//--------------------------------

		// MOVEMENT LEFT
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (tempPos.x >= App->render->camera.x)
				playerData.pos.x -= 4;
			animation = &running;
		}
		//--------------------------------
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		ability_boost = true;

	// PUNCHES
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && is_punching == false)
	{
		is_punching = true;	
		punch.Reset();
		punch.ResetLoops();
		punch_barrage.Reset();
		punch_barrage.ResetLoops();
	}
	if (is_punching)
	{
		if (ability_boost)
		{
			animation = &punch_barrage;
		}
		else
		{ 
			animation = &punch;
		}
		if (!offset_x_added && looking_left)
		{
			playerData.pos.x -= animation->offset_x;
			offset_x_added = true;
		}
		if (!offset_y_added)
		{
			playerData.pos.y += animation->offset_y;
			offset_y_added = true;
		}

		if (animation->Finished())
		{
			if (offset_x_added)
			{
				playerData.pos.x += animation->offset_x;
				offset_x_added = false;
			}
			if (offset_y_added)
			{
				playerData.pos.y -= animation->offset_y;
				offset_y_added = false;
			}
			is_punching = false;	
			ability_boost = false;
			animation = &idle;
		}
	}
	//--------------------------------

	// KICKS
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && is_kicking == false)
	{
		is_kicking = true;
		kick.Reset();
		kick.ResetLoops();
		double_kick.Reset();
		double_kick.ResetLoops();
	}
	if (is_kicking)
	{
		if (ability_boost)
		{
			animation = &double_kick;
		}
		else
		{
			animation = &kick;
		}
		if (!offset_x_added && looking_left)
		{
			playerData.pos.x -= animation->offset_x;
			offset_x_added = true;
		}
		if (!offset_y_added)
		{
			playerData.pos.y += animation->offset_y;
			offset_y_added = true;
		}

		if (animation->Finished())
		{
			if (offset_x_added)
			{
				playerData.pos.x += animation->offset_x;
				offset_x_added = false;
			}
			if (offset_y_added)
			{
				playerData.pos.y -= animation->offset_y;
				offset_y_added = false;
			}
			is_kicking = false;
			ability_boost = false;
			animation = &idle;
		}
	}
	//--------------------------------

	//UNSHEATHE SWORD
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		unsheathing = true;
		sword = !sword;
		unsheathe.Reset();
		unsheathe.ResetLoops();
	}

	if (sword && unsheathing)
	{
		animation = &unsheathe;
		if (animation->Finished())
		{
			unsheathing = false;
		}
	}

	App->render->Blit(texture, playerData.pos.x, playerData.pos.y, &animation->GetCurrentFrame(), 1, flip);
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

void ModulePlayer::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
	animation->offset_x = animation_node.attribute("offset_x").as_int();
	animation->offset_y = animation_node.attribute("offset_y").as_int();
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