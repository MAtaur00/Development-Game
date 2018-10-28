#ifndef _j1PLAYER_H__
#define _j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Render.h"

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

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void FindPlayerSpawn();

	void SpawnPLayer();

public:

	Animation* animation = nullptr;

	Animation idle = Animation();
	Animation running = Animation();
	Animation jumping = Animation();
	Animation die = Animation();
	Animation slide = Animation();
	Animation fall = Animation();
	Animation wall_slide = Animation();
	Animation punch = Animation();
	Animation punch_barrage = Animation();
	Animation kick = Animation();
	Animation double_kick = Animation();
	Animation unsheathe = Animation();
	Animation idle_sword = Animation();

	PlayerData playerData;

	int cont = 0;
	int timer_second_punch = 0;
	
	bool sword = false;
	bool unsheathing = false;
	bool is_punching = false;
	bool is_kicking = false;
	bool is_jumping;
	bool is_falling;
	bool can_jump;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	bool ability_boost = false;

	bool looking_right = false;
	bool looking_left = false;

	bool god_mode = false;

	bool offset_x_added = false;
	bool offset_y_added = false;

	p2Point<int> spawn;

	SDL_Texture* texture = nullptr;

};

#endif