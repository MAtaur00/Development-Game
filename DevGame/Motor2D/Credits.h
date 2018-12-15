#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "j1Module.h"
#include "Label.h"
#include "Image.h"

class Credits : public j1Module
{
public:
	Credits();
	~Credits();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	/*bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void CreateMenu();*/

public:

	Image* bg_image = nullptr;

	Label* credits_label = nullptr;
};


#endif // __CREDITS_H__