#include "StartMenu.h"

StartMenu::StartMenu(void){
	buttons.push_back(UIManager::GetInstance().CreateButton("New Game",(WindowManager::GetInstance().GetWindowWidth() / 2) - 75,(WindowManager::GetInstance().GetWindowHeight() / 2) - 80,150,50,[](void){ MenuManager::GetInstance().GetStartMenu()->SetIsCreating(true); },23));
	buttons.push_back(UIManager::GetInstance().CreateButton("Load Game",(WindowManager::GetInstance().GetWindowWidth() / 2) - 75,(WindowManager::GetInstance().GetWindowHeight() / 2) - 20,150,50,[](void){ MenuManager::GetInstance().GetStartMenu()->SetIsLoading(true); },23));
	buttons.push_back(UIManager::GetInstance().CreateButton("Quit Game",(WindowManager::GetInstance().GetWindowWidth() / 2) - 75,(WindowManager::GetInstance().GetWindowHeight() / 2) + 40,150,50,[](void){ MenuManager::GetInstance().GetStartMenu()->SetIsQuitting(true); },23));
	isCreating = false;
	isLoading = false;
	isQuitting = false;
	creatingPath = "";
	loadPath = "";
}

StartMenu::~StartMenu(void){
	for(unsigned int i = 0;i < buttons.size();i++){
		UIManager::GetInstance().RemoveButton(buttons[i]);
	}
	buttons.clear();
}

void StartMenu::SetCreatingPath(std::string setCreatingPath){
	creatingPath = setCreatingPath;
}

void StartMenu::SetLoadPath(std::string setLoadPath){
	loadPath = setLoadPath;
}

std::string StartMenu::GetCreatingPath(void){
	return creatingPath;
}

std::string StartMenu::GetLoadPath(void){
	return loadPath;
}

void StartMenu::SetIsCreating(bool setIsCreating){
	isCreating = setIsCreating;
}

void StartMenu::SetIsLoading(bool setIsLoading){
	isLoading = setIsLoading;
}

void StartMenu::SetIsQuitting(bool setIsQuitting){
	isQuitting = setIsQuitting;
}

bool StartMenu::GetIsCreating(void){
	return isCreating;
}

bool StartMenu::GetIsLoading(void){
	return isLoading;
}

bool StartMenu::GetIsQuitting(void){
	return isQuitting;
}
