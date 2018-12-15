#ifndef _COIN_H__
#define _COIN_H__

#include "Entity.h"
#include "ModuleEntities.h"
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Render.h"

struct SDL_Texture;

class Coin : public Entity
{
public:

	Coin(int x, int y, ENTITY_TYPE type);
	~Coin();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

public:
	Animation coinRot = Animation();


	EntityData coinData;

	iPoint coinPos;
	iPoint playerPos;
	fPoint playerPosition;
	iPoint nextPoint;
	iPoint spawnPos;

	fPoint spawn;

	int coin_counter = 0;
};

#endif // !_COIN_H__