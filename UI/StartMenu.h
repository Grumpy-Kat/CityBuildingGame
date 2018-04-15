#ifndef UI_STARTMENU_H_
#define UI_STARTMENU_H_

#include "Button.h"
#include "../UIManager.h"
#include <vector>
#include <string>

class StartMenu {
public:
	StartMenu(void);
	~StartMenu(void);

	void SetCreatingPath(std::string setCreatingPath);
	void SetLoadPath(std::string setLoadPath);

	std::string GetCreatingPath(void);
	std::string GetLoadPath(void);

	void SetIsCreating(bool setIsCreating);
	void SetIsLoading(bool setIsLoading);
	void SetIsQuitting(bool setIsQuitting);

	bool GetIsCreating(void);
	bool GetIsLoading(void);
	bool GetIsQuitting(void);
private:
	std::vector<Button> buttons;

	std::string creatingPath;
	std::string loadPath;

	bool isCreating;
	bool isLoading;
	bool isQuitting;
};

#endif
