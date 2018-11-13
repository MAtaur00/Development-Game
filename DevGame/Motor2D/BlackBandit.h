#ifndef _BLACKBANDIT_H__
#define _BLACKBANDIT_H__

#include "Entity.h"
#include "ModuleEntities.h"
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Render.h"

struct SDL_Texture;

class BlackBandit : public Entity
{
public:

	BlackBandit(int x, int y, ENTITY_TYPE type);
	~BlackBandit();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void FindSpawn();

	void Spawn();

public:
	Animation idle = Animation();
	Animation idleSwordUp = Animation();
	Animation running = Animation();
	Animation attack = Animation();
	Animation death = Animation();

	p2Point<int> spawn;

};

#endif // !_BLACKBANDIT_H_