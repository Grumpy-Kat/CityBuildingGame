#ifndef UI_SAVEMENU_H_
#define UI_SAVEMENU_H_

#include "TextBox.h"
#include "../UIManager.h"

class SaveMenu {
public:
	SaveMenu();
	~SaveMenu();
private:
	std::vector<TextBox> textBoxes;
};

#endif
