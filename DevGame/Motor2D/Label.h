#ifndef __LABEL_H__
#define __LABEL_H__

#include "UI.h"
#include "p2SString.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

class Label : public UI_Element
{
public:

	Label(int x, int y, UI_Element* parent, j1Module* CallBack);
	~Label();

	bool Update(float dt);
	bool CleanUp();

	bool SetText(char* text);

	bool Draw();

public:

	p2SString text;

};

#endif