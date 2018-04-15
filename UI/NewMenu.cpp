#include "NewMenu.h"

NewMenu::NewMenu(void){
	int window = WindowManager::GetInstance().CreateNewWindow(350,300,"New",{ 127,127,127,255 });
	std::function<bool(std::string)> validate = [](std::string fileName){ return MenuManager::GetInstance().GetNewMenu()->Validate(fileName); };
	textBoxes.push_back(UIManager::GetInstance().CreateTextBox("Create","/maps/","Image",0,0,[](std::string fileName){ MenuManager::GetInstance().GetStartMenu()->SetCreatingPath(fileName); },validate,false,window));
}

NewMenu::~NewMenu(void){
	for(unsigned int i = 0;i < textBoxes.size();i++){
		UIManager::GetInstance().RemoveTextBox(textBoxes[i]);
	}
	textBoxes.clear();
}

bool NewMenu::Validate(std::string fileName){
	std::cout << "NewMenu::Validate: 0 " << fileName << std::endl;
	std::ifstream file(fileName);
	std::cout << "NewMenu::Validate: 1 " << ((bool)file) << std::endl;
	return (bool)file;
}
