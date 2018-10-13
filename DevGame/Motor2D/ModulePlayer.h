#ifndef _j1PLAYER_H__
#define _j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

enum COLLISION_TYPE
{
	GROUND,
	AIR,
	DEATH,
	WIN
};

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

	int player_width = 25;
	int player_height = 30;

	fPoint pos;

	float speed = 600.0f;
	float jumpSpeed = 800.0f;

	ANIMATION_STATE anim_state;
};

class ModulePlayer : public j1Module
{
public:

	ModulePlayer();
	virtual ~ModulePlayer();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void SpawnPLayer();

	int GetPlayerTile(fPoint pos) const;

	COLLISION_TYPE CheckCollision(int x) const;

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
	Animation die_right = Animation();
	Animation die_left = Animation();
	Animation slide_right = Animation();
	Animation slide_left = Animation();

	PlayerData playerData;

	fPoint initial_pos;

	bool looking_right = false;
	bool looking_left = false;

	SDL_Texture* texture = nullptr;

};

#endif