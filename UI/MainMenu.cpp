#include "MainMenu.h"

MainMenu::MainMenu(void){
	buttons.push_back(UIManager::GetInstance().CreateButton("images/Tile/GrassTile.png",4,3,32,32,5,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("None"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/Residential/0.png",4,3,32,32,50,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Residential"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/Commercial/4.png",4,3,32,32,95,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Commercial"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/Industrial/7.png",4,3,32,32,140,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Industrial"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/Road/_NS.png",4,3,32,32,185,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Road"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/PowerlineStanding/_EW.png",4,3,32,32,230,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Powerline"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/CoalPowerplant/Default.png",4,3,32,32,275,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Coal Powerplant"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("images/FireStation/Default.png",4,3,32,32,320,WindowManager::GetInstance().GetWindowHeight()-45,40,40,[](void){ MouseManager::GetInstance().SetBuildingType("Fire Station"); }));
	buttons.push_back(UIManager::GetInstance().CreateButton("Open Loan Menu",WindowManager::GetInstance().GetWindowWidth()-165,5,160,40,[](void){ MenuManager::GetInstance().CreateLoanMenu(); },20));
	buttons.push_back(UIManager::GetInstance().CreateButton("Open Tax Menu",WindowManager::GetInstance().GetWindowWidth()-165,50,160,40,[](void){ MenuManager::GetInstance().CreateTaxMenu(); },20));
	text.push_back(SpriteManager::GetInstance().CreateSprite("Money: ",{255,255,255,255},20,40,15));
	UpdateMoneySprite(true);
	text.push_back(SpriteManager::GetInstance().CreateSprite("Population: ",{255,255,255,255},20,56,40));
	UpdatePopSprite(true);
	buttons.push_back(UIManager::GetInstance().CreateButton("Save",WindowManager::GetInstance().GetWindowWidth()-105,WindowManager::GetInstance().GetWindowHeight()-45,100,40,[](void){ MenuManager::GetInstance().CreateSaveMenu(); },20));
}

MainMenu::~MainMenu(void){
	for(unsigned int i = 0;i < buttons.size();i++){
		UIManager::GetInstance().RemoveButton(buttons[i]);
	}
	buttons.clear();
	for(unsigned int i = 0;i < text.size();i++){
		SpriteManager::GetInstance().RemoveSprite(text[i],"ui");
	}
	text.clear();
}

void MainMenu::UpdateMoneySprite(bool creating){
	if(!creating){
		SpriteManager::GetInstance().RemoveSprite(text[1],"ui");
	}
	std::stringstream strs;
	strs << MoneyManager::GetInstance().GetAmount();
	std::string temp_str = strs.str();
	int width = 0,height = 0;
	TTF_Font *font = TTF_OpenFont("fonts/ARIAL.TTF",20);
	TTF_SizeText(font,temp_str.c_str(),&width,&height);
	font = nullptr;
	if(text.size() > 1){
		text[1] = SpriteManager::GetInstance().CreateSprite(temp_str.c_str(),{255,255,255,255},20,75 + (width / 2),15);
	} else{
		text.push_back(SpriteManager::GetInstance().CreateSprite(temp_str.c_str(),{255,255,255,255},20,75 + (width / 2),15));
	}
}

void MainMenu::UpdatePopSprite(bool creating){
	if(!creating){
		SpriteManager::GetInstance().RemoveSprite(text[3],"ui");
	}
	int pop = PopulationManager::GetInstance().GetRedPop() + PopulationManager::GetInstance().GetComPop() + PopulationManager::GetInstance().GetIndPop();
	std::stringstream strs;
	strs << pop;
	std::string temp_str = strs.str();
	int width = 0,height = 0;
	TTF_Font *font = TTF_OpenFont("fonts/ARIAL.TTF",20);
	TTF_SizeText(font,temp_str.c_str(),&width,&height);
	font = nullptr;
	if(text.size() > 3){
		text[3] = SpriteManager::GetInstance().CreateSprite(temp_str.c_str(),{255,255,255,255},20,105 + (width / 2),40);
	} else{
		text.push_back(SpriteManager::GetInstance().CreateSprite(temp_str.c_str(),{255,255,255,255},20,105 + (width / 2),40));
	}
}
