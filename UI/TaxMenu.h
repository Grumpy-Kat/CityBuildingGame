#ifndef UI_TAXMENU_H_
#define UI_TAXMENU_H_

#include "TextField.h"
#include "../WindowManager.h"

class TaxMenu {
public:
	TaxMenu();
	~TaxMenu();

	void UpdateRedTextField(void);
	void UpdateComTextField(void);
	void UpdateIndTextField(void);
private:
	std::vector<Sprite> text;
	std::vector<TextField> textFields;
};

#endif
