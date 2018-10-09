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

	//jumping right animation
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.PushBack({ 17, 126, 36, 38 });
	jumping_right.speed = 0.05f;
	jumping_right.loop = false;

	//jumping left animation
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.PushBack({ 405, 121, 35, 38 });
	jumping_left.speed = 0.05f;
	jumping_left.loop = false;

}
ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start()
{
	texture = App->tex->Load("textures/Player/player_spritesheet.png");

	playerData.pos.x = 35;
	playerData.pos.y = 448;
	return true;
}

bool ModulePlayer::Update()
{
	animation = &idle_right;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{

		playerData.pos.x += 1;
		animation = &running_right;

	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{

		playerData.pos.x -= 1;
		animation = &running_left;

	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		playerData.pos.y -= 1;
		animation = &jumping_right;
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
	playerData.x = data.child("pos").attribute("x").as_int();
	playerData.y = data.child("pos").attribute("y").as_int();

	return true;
}

bool ModulePlayer::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("pos");

	position.append_attribute("x") = (int)playerData.x;
	position.append_attribute("y") = (int)playerData.y;

	return true;
}