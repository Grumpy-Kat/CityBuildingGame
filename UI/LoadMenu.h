#ifndef UI_LOADMENU_H_
#define UI_LOADMENU_H_

#include "TextBox.h"
#include "../UIManager.h"
#include <string>
#include <fstream>

class LoadMenu {
public:
	LoadMenu(void);
	~LoadMenu(void);

	bool Validate(std::string fileName);
private:
	std::vector<TextBox> textBoxes;
};

#endif
