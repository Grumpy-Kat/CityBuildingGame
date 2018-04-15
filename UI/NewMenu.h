#ifndef UI_NEWMENU_H_
#define UI_NEWMENU_H_

#include "TextBox.h"
#include "../UIManager.h"
#include <vector>
#include <fstream>

class NewMenu {
public:
	NewMenu(void);
	~NewMenu(void);

	bool Validate(std::string fileName);
private:
	std::vector<TextBox> textBoxes;
};

#endif
