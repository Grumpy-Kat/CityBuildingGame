#include "PopulationManager.h"

PopulationManager::PopulationManager(void){
}

PopulationManager::~PopulationManager(void){
}

void PopulationManager::Start(void){
	redPop = 0;
	comPop = 0;
	indPop = 0;
	redPool = 100;
	comPool = 100;
	indPool = 100;
}

PopulationManager &PopulationManager::GetInstance(void){
	static PopulationManager *instance = nullptr;
	if(instance == nullptr){
		instance = new PopulationManager;
	}
	return *instance;
}

void PopulationManager::AddRedPop(int addPop){
	redPop += addPop;
	if(redPop < 0){
		redPop = 0;
	}
	MenuManager::GetInstance().GetMainMenu()->UpdatePopSprite();
}

void PopulationManager::AddComPop(int addPop){
	comPop += addPop;
	if(comPop < 0){
		comPop = 0;
	}
	MenuManager::GetInstance().GetMainMenu()->UpdatePopSprite();
}

void PopulationManager::AddIndPop(int addPop){
	indPop += addPop;
	if(indPop < 0){
		indPop = 0;
	}
	MenuManager::GetInstance().GetMainMenu()->UpdatePopSprite();
}

int PopulationManager::GetRedPop(void){
	return redPop;
}

int PopulationManager::GetComPop(void){
	return comPop;
}

int PopulationManager::GetIndPop(void){
	return indPop;
}

void PopulationManager::AddRedPool(int addPool){
	redPool += addPool;
	if(redPool < 0){
		redPool = 0;
	}
}

void PopulationManager::AddComPool(int addPool){
	comPool += addPool;
	if(comPool < 0){
		comPool = 0;
	}
}

void PopulationManager::AddIndPool(int addPool){
	indPool += addPool;
	if(indPool < 0){
		indPool = 0;
	}
}

int PopulationManager::GetRedPool(void){
	return redPool;
}

int PopulationManager::GetComPool(void){
	return comPool;
}

int PopulationManager::GetIndPool(void){
	return indPool;
}
