#include "UI.h"
#include "p2SString.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

class Label : public UI_Element
{
private:

public:

	Label(int x, int y, UI_Element* parent);
	~Label();

	bool Update(float dt);
	bool CleanUp();

	bool SetText(char* text);

public:

	p2SString text;

};