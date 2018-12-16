#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Timer.h"

struct SDL_Texture;

#include "Image.h"
#include "Label.h"

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load
	bool Load(pugi::xml_node& savegame);

	bool LoadScene(int map = -1);

	//Save
	bool Save(pugi::xml_node& data) const;

	int currmap = 1;

	bool loadScene = false;

	j1Timer game_time, pause_time;

	bool vsyncCont;

	Image* ui_coin = nullptr;

	Label* game_time_label;

	uint saved_time = 0;

	bool pause = false;

	int coins_collected;

	uint timer_pause = 0u;
	uint timer_game;
	int start_time = 0;

	bool first_load = true;

	Label* coin_score = nullptr;

	Image* life1 = nullptr;
	Image* life2 = nullptr;
	Image* life3 = nullptr;

	int map = 1;

	int lives = 3;

private:

	p2List<const char*>  MapsList_String;
	p2List_item<const char*>* CurrentMap = nullptr;
	
};

#endif // __j1SCENE_H__