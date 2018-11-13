#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Entity.h"
#include "ModuleEntities.h"
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Render.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player(int x, int y, ENTITY_TYPE type);
	~Player();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetPlayerTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void FindPlayerSpawn();

	void SpawnPLayer();

public:
	Animation idle = Animation();
	Animation running = Animation();
	Animation jumping = Animation();
	Animation death = Animation();
	Animation slide = Animation();
	Animation fall = Animation();
	Animation wall_slide = Animation();
	Animation punch1 = Animation();
	Animation punch2 = Animation();
	Animation punch3 = Animation();
	Animation punch_barrage = Animation();
	Animation kick1 = Animation();
	Animation kick2 = Animation();
	Animation double_kick = Animation();
	Animation unsheathe = Animation();
	Animation sheathe = Animation();
	Animation idle_sword = Animation();
	Animation running_sword = Animation();
	Animation slash1 = Animation();
	Animation triple_slash = Animation();

	int cont = 0;
	int timer_second_punch = 0;

	bool sword = false;
	bool unsheathing = false;
	bool sheathing = false;
	bool is_punching = false;
	bool is_kicking = false;
	bool is_slashing = false;
	bool is_jumping;
	bool is_falling;
	bool can_jump;
	bool on_the_floor;

	bool ability_boost = false;

	bool looking_right = false;
	bool looking_left = false;

	bool god_mode = false;

	bool offset_x_added = false;
	bool offset_y_added = false;

	p2Point<int> spawn;

	EntityData playerData;
};

#endif // !_PLAYER_H_