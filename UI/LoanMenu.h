#ifndef UI_LOANMENU_H_
#define UI_LOANMENU_H_

#include "Button.h"
#include "../UIManager.h"
#include "../MoneyManager.h"
#include <vector>

class LoanMenu {
public:
	LoanMenu(void);
	~LoanMenu(void);

	void UpdateText(int amt,bool on);
private:
	std::vector<Button> buttons;
	std::vector<Sprite> text;
};

#endif
