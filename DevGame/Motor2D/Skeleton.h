#ifndef _SKELETON_H__
#define _SKELETON_H__

#include "Entity.h"
#include "ModuleEntities.h"
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Render.h"

struct SDL_Texture;

class Skeleton : public Entity
{
public:

	Skeleton(int x, int y, ENTITY_TYPE type);
	~Skeleton();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

public:
	Animation idle = Animation();
	Animation notice = Animation();
	Animation hit = Animation();
	Animation walk = Animation();
	Animation death = Animation();

	EntityData skeletonData;

	iPoint skeletonPos;
	iPoint playerPos;
	fPoint playerPosition;
	iPoint nextPoint;
	iPoint spawnPos;

	fPoint spawn;
};

#endif // !_SKELETON_H_