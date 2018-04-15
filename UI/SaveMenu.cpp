#include "SaveMenu.h"

SaveMenu::SaveMenu(void){
	int window = WindowManager::GetInstance().CreateNewWindow(350,300,"Save",{ 127,127,127,255 });
	std::function<bool(std::string)> validate = [](std::string fileName){ return true; };
	textBoxes.push_back(UIManager::GetInstance().CreateTextBox("Save","saves/","Text",0,0,[](std::string fileName){  WorldManager::GetInstance().GetWorld()->Save(fileName); },validate,false,window));
}

SaveMenu::~SaveMenu(void){
	for(unsigned int i = 0;i < textBoxes.size();i++){
		UIManager::GetInstance().RemoveTextBox(textBoxes[i]);
	}
	textBoxes.clear();
}
