#include "LoanMenu.h"

LoanMenu::LoanMenu(void){
	int window = WindowManager::GetInstance().CreateNewWindow(395,220,"Loan",{ 127,127,127,255 });
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 1000 Loan",5,55,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(1000); },19,window));
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 5000 Loan",200,55,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(5000); },19,window));
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 10000 Loan",5,110,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(10000); },19,window));
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 25000 Loan",200,110,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(25000); },19,window));
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 100000 Loan",5,165,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(100000); },19,window));
	buttons.push_back(UIManager::GetInstance().CreateButton("Take Out 500000 Loan",200,165,190,50,[](void){ MoneyManager::GetInstance().TakeLoan(500000); },19,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("Loans",{ 0,0,0,255 },23,197.5,17,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("(One Percent Interest Per Month)",{ 0,0,0,255 },17,197.5,40,window));
}

LoanMenu::~LoanMenu(void){
	for(unsigned int i = 0;i < buttons.size();i++){
		UIManager::GetInstance().RemoveButton(buttons[i]);
	}
	buttons.clear();
	for(unsigned int i = 0;i < text.size();i++){
		SpriteManager::GetInstance().RemoveSprite(text[i],"ui");
	}
	text.clear();
}

void LoanMenu::UpdateText(int amt,bool on){
	int i = -1;
	if(amt == 1000){
		i = 0;
	} else if(amt == 5000){
		i = 1;
	} else if(amt == 10000){
		i = 2;
	} else if(amt == 25000){
		i = 3;
	} else if(amt == 100000){
		i = 4;
	} else if(amt == 500000){
		i = 5;
	}
	if(i != -1){
		std::string text;
		std::stringstream strs;
		strs << amt;
		std::string temp_str = strs.str();
		if(on){
			text = std::string("Take Out ");
		} else{
			text = std::string("Pay Back ");
		}
		text += temp_str;
		text += std::string(" Loan");
		buttons[i].ChangeText(text);
	}
}
