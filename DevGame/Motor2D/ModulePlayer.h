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

	fPoint pos;

	float speed = 2.0f;
	float jumpSpeed = 2.0f;
	float gravity = 3.0f;

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

	int GetPlayerTile(fPoint pos) const;

	COLLISION_TYPE CheckCollision(int x) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void FindPlayerSpawn();

	void SpawnPLayer();

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
	Animation fall_right = Animation();
	Animation fall_left = Animation();
	Animation wall_slide_right = Animation();
	Animation wall_slide_left = Animation();

	PlayerData playerData;

	int cont = 0;

	bool is_jumping;
	bool is_falling;
	bool can_jump;

	bool looking_right = false;
	bool looking_left = false;

	bool god_mode = false;

	p2Point<int> spawn;

	SDL_Texture* texture = nullptr;

};

#endif