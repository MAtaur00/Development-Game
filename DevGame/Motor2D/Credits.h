#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "j1Module.h"
#include "Label.h"
#include "Image.h"
#include "Button.h"

class Credits : public j1Module
{
public:
	Credits();
	~Credits();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void CallBack(UI_Element* element);

public:

	Image* bg_image = nullptr;

	Button* button_credits_back = nullptr;
};


#endif // __CREDITS_H__