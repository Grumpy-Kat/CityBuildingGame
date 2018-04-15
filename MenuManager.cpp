#include "MenuManager.h"

MenuManager::MenuManager(void){
}

MenuManager::~MenuManager(void){
}

void MenuManager::Start(void){
	mainMenu = nullptr;
	startMenu = nullptr;
	newMenu = nullptr;
	loadMenu = nullptr;
	saveMenu = nullptr;
	loanMenu = nullptr;
	taxMenu = nullptr;
}

void MenuManager::End(void){
	mainMenu = nullptr;
	startMenu = nullptr;
	newMenu = nullptr;
	loadMenu = nullptr;
	saveMenu = nullptr;
	loanMenu = nullptr;
	taxMenu = nullptr;
}

MenuManager &MenuManager::GetInstance(void){
	static MenuManager *instance = nullptr;
	if(instance == nullptr){
		instance = new MenuManager;
	}
	return *instance;
}

void MenuManager::CreateMainMenu(void){
	if(mainMenu == nullptr){
		mainMenu = new MainMenu();
	}
}

void MenuManager::CloseMainMenu(void){
	mainMenu = nullptr;
}

MainMenu *&MenuManager::GetMainMenu(void){
	return mainMenu;
}

void MenuManager::CreateStartMenu(void){
	if(startMenu == nullptr){
		startMenu = new StartMenu();
	}
}

void MenuManager::CloseStartMenu(void){
	startMenu = nullptr;
}

StartMenu *&MenuManager::GetStartMenu(void){
	return startMenu;
}

void MenuManager::CreateNewMenu(void){
	if(newMenu == nullptr){
		newMenu = new NewMenu();
	}
}

void MenuManager::CloseNewMenu(void){
	newMenu = nullptr;
}

NewMenu *&MenuManager::GetNewMenu(void){
	return newMenu;
}

void MenuManager::CreateLoadMenu(void){
	if(loadMenu == nullptr){
		loadMenu = new LoadMenu();
	}
}

void MenuManager::CloseLoadMenu(void){
	loadMenu = nullptr;
}

LoadMenu *&MenuManager::GetLoadMenu(void){
	return loadMenu;
}

void MenuManager::CreateSaveMenu(void){
	if(saveMenu == nullptr){
		saveMenu = new SaveMenu();
	}
}

void MenuManager::CloseSaveMenu(void){
	saveMenu = nullptr;
}

SaveMenu *&MenuManager::GetSaveMenu(void){
	return saveMenu;
}

void MenuManager::CreateLoanMenu(void){
	if(loanMenu == nullptr){
		loanMenu = new LoanMenu();
	}
}

void MenuManager::CloseLoanMenu(void){
	loanMenu = nullptr;
}

LoanMenu *&MenuManager::GetLoanMenu(void){
	return loanMenu;
}

void MenuManager::CreateTaxMenu(void){
	if(taxMenu == nullptr){
		taxMenu = new TaxMenu();
	}
}

void MenuManager::CloseTaxMenu(void){
	taxMenu = nullptr;
}

TaxMenu *&MenuManager::GetTaxMenu(void){
	return taxMenu;
}
