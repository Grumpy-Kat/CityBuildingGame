#include "LoadMenu.h"

LoadMenu::LoadMenu(void){
	int window = WindowManager::GetInstance().CreateNewWindow(350,300,"Load",{ 127,127,127,255 });
	std::function<bool(std::string)> validate = [](std::string fileName){ std::cout << "validate" << std::endl; return MenuManager::GetInstance().GetLoadMenu()->Validate(fileName); };
	//textBoxes.push_back(UIManager::GetInstance().CreateTextBox("Load","",0,0,[](std::string fileName){ MenuManager::GetInstance().GetStartMenu()->SetLoadPath("saves/" + fileName + ".txt"); },validate,window));
	textBoxes.push_back(UIManager::GetInstance().CreateTextBox("Load","/saves/","List",0,0,[](std::string fileName){ MenuManager::GetInstance().GetStartMenu()->SetLoadPath(fileName); },validate,true,window));
}

LoadMenu::~LoadMenu(void){
	for(unsigned int i = 0;i < textBoxes.size();i++){
		UIManager::GetInstance().RemoveTextBox(textBoxes[i]);
	}
	textBoxes.clear();
}

bool LoadMenu::Validate(std::string fileName){
	std::ifstream file(fileName);
	std::cout << fileName << " | " << (bool)file << std::endl;
	//return file.good();
	return (bool)file;
}
