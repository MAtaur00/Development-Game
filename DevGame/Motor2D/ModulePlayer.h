#ifndef _j1PLAYER_H__
#define _j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

enum ANIMATION_STATE 
{
	IDLE_LEFT,
	IDLE_RIGHT,
	RUNNING_LEFT,
	RUNNING_RIGHT,
	JUMPING_LEFT,
	JUMPING_RIGHT
};

struct PlayerData 
{

	iPoint pos;
	float x, y, w, h;

	float speed = 350.0f;
	float jumpSpeed = 800.0f;

	ANIMATION_STATE anim_state;
};

class ModulePlayer : public j1Module
{
public:

	ModulePlayer();
	virtual ~ModulePlayer();

	bool Start();
	bool Update();
	bool CleanUp();

	void SpawnPLayer();

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

public:

	Animation* animation = nullptr;

	Animation idle_right = Animation();
	Animation idle_left = Animation();
	Animation running_right = Animation();
	Animation running_left = Animation();
	Animation jumping_right = Animation();
	Animation jumping_left = Animation();

	PlayerData playerData;

	SDL_Texture* texture = nullptr;

};

#endif