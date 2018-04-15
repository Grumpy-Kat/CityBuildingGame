#ifndef MENUMANAGER_H_
#define MENUMANAGER_H_

#include "UI/MainMenu.h"
#include "UI/StartMenu.h"
#include "UI/NewMenu.h"
#include "UI/LoadMenu.h"
#include "UI/SaveMenu.h"
#include "UI/LoanMenu.h"
#include "UI/TaxMenu.h"

class MainMenu;
class StartMenu;
class NewMenu;
class LoadMenu;
class SaveMenu;
class LoanMenu;
class TaxMenu;

class MenuManager {
public:
	~MenuManager(void);

	void Start(void);
	void End(void);

	static MenuManager &GetInstance(void);

	void CreateMainMenu(void);
	void CloseMainMenu(void);
	MainMenu *&GetMainMenu(void);

	void CreateStartMenu(void);
	void CloseStartMenu(void);
	StartMenu *&GetStartMenu(void);

	void CreateNewMenu(void);
	void CloseNewMenu(void);
	NewMenu *&GetNewMenu(void);

	void CreateLoadMenu(void);
	void CloseLoadMenu(void);
	LoadMenu *&GetLoadMenu(void);

	void CreateSaveMenu(void);
	void CloseSaveMenu(void);
	SaveMenu *&GetSaveMenu(void);

	void CreateLoanMenu(void);
	void CloseLoanMenu(void);
	LoanMenu *&GetLoanMenu(void);

	void CreateTaxMenu(void);
	void CloseTaxMenu(void);
	TaxMenu *&GetTaxMenu(void);
private:
	MenuManager(void);

	MainMenu *mainMenu;

	StartMenu *startMenu;

	NewMenu *newMenu;

	LoadMenu *loadMenu;

	SaveMenu *saveMenu;

	LoanMenu *loanMenu;

	TaxMenu *taxMenu;
};

#endif
