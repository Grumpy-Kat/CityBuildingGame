#include "TaxMenu.h"

TaxMenu::TaxMenu() {
	int window = WindowManager::GetInstance().CreateNewWindow(395,220,"Tax",{ 127,127,127,255 });
	text.push_back(SpriteManager::GetInstance().CreateSprite("Tax Rates",{ 0,0,0,255 },23,197.5,17,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("Residential Tax:",{ 0,0,0,255 },20,74,55,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("Commercial Tax:",{ 0,0,0,255 },20,79,80,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("Industrial Tax:",{ 0,0,0,255 },20,65,105,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("%",{ 0,0,0,255 },20,203,55,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("%",{ 0,0,0,255 },20,213,80,window));
	text.push_back(SpriteManager::GetInstance().CreateSprite("%",{ 0,0,0,255 },20,185,105,window));
	std::stringstream strsRed;
	strsRed << MoneyManager::GetInstance().GetRedTax();
	std::string temp_str = strsRed.str();
	textFields.push_back(UIManager::GetInstance().CreateTextField(temp_str.c_str(),148,48,50,19,[](std::string val){ MoneyManager::GetInstance().SetRedTax(val); },19,window));
	std::stringstream strsCom;
	strsCom << MoneyManager::GetInstance().GetComTax();
	temp_str = strsCom.str();
	textFields.push_back(UIManager::GetInstance().CreateTextField(temp_str.c_str(),158,73,50,19,[](std::string val){ MoneyManager::GetInstance().SetComTax(val); },19,window));
	std::stringstream strsInd;
	strsInd << MoneyManager::GetInstance().GetIndTax();
	temp_str = strsInd.str();
	textFields.push_back(UIManager::GetInstance().CreateTextField(temp_str.c_str(),130,98,50,19,[](std::string val){ MoneyManager::GetInstance().SetIndTax(val); },19,window));
}

TaxMenu::~TaxMenu() {
	for(unsigned int i = 0;i < text.size();i++){
		SpriteManager::GetInstance().RemoveSprite(text[i],"ui");
	}
	text.clear();
	for(unsigned int i = 0;i < textFields.size();i++){
		UIManager::GetInstance().RemoveTextField(textFields[i]);
	}
	textFields.clear();
}

void TaxMenu::UpdateRedTextField(void){
	std::stringstream strs;
	strs << MoneyManager::GetInstance().GetRedTax();
	std::string temp_str = strs.str();
	textFields[0].SetText(temp_str);
}

void TaxMenu::UpdateComTextField(void){
	std::stringstream strs;
	strs << MoneyManager::GetInstance().GetComTax();
	std::string temp_str = strs.str();
	textFields[1].SetText(temp_str);
}
void TaxMenu::UpdateIndTextField(void){
	std::stringstream strs;
	strs << MoneyManager::GetInstance().GetIndTax();
	std::string temp_str = strs.str();
	textFields[2].SetText(temp_str);
}
