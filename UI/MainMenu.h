#ifndef UI_MAINMENU_H_
#define UI_MAINMENU_H_

#include "Button.h"
#include "../MoneyManager.h"
#include "../PopulationManager.h"
#include "../MouseManager.h"
#include "../Sprite.h"
#include "../SpriteManager.h"
#include "../UIManager.h"
#include "../WorldManager.h"
#include <vector>
#include <sstream>
#include <string>

class Sprite;
class Button;

class MainMenu {
public:
	MainMenu(void);
	~MainMenu(void);

	void UpdateMoneySprite(bool creating = false);
	void UpdatePopSprite(bool creating = false);
private:
	std::vector<Button> buttons;
	std::vector<Sprite> text;
};

#endif
