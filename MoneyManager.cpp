#include "MoneyManager.h"

MoneyManager::MoneyManager(void){
}


MoneyManager::~MoneyManager(void){
}

void MoneyManager::Start(void){
	amt = 0;
	loans[1000] = false;
	loans[5000] = false;
	loans[10000] = false;
	loans[25000] = false;
	loans[100000] = false;
	loans[500000] = false;
	redTax = 7;
	comTax = 7;
	indTax = 7;
}

MoneyManager &MoneyManager::GetInstance(void){
	static MoneyManager *instance = nullptr;
	if(instance == nullptr){
		instance = new MoneyManager;
	}
	return *instance;
}

void MoneyManager::AddAmount(int addAmt){
	amt += addAmt;
	MenuManager::GetInstance().GetMainMenu()->UpdateMoneySprite();
}

int MoneyManager::GetAmount(void){
	return amt;
}

void MoneyManager::TakeLoan(int amount){
	if(loans.find(amount) != loans.end() && !loans[amount]){
		loans[amount] = true;
		amt += amount;
		MenuManager::GetInstance().GetLoanMenu()->UpdateText(amount,false);
	} else if(loans.find(amount) != loans.end() && amt - amount > -1000){
		loans[amount] = false;
		amt -= amount;
		MenuManager::GetInstance().GetLoanMenu()->UpdateText(amount,true);
	}
	MenuManager::GetInstance().GetMainMenu()->UpdateMoneySprite();
}

void MoneyManager::SubtractLoanInterest(void){
	for(std::map<int,bool>::iterator it = loans.begin();it != loans.end();it++) {
		if(it->second){
			amt -= it->first * 0.05;
		}
	}
	MenuManager::GetInstance().GetMainMenu()->UpdateMoneySprite();
}

bool MoneyManager::GetLoanInfo(int amount){
	return loans[amount];
}

void MoneyManager::SetRedTax(std::string setRed){
	redTax = atoi(setRed.c_str());
}

void MoneyManager::SetComTax(std::string setCom){
	comTax = atoi(setCom.c_str());
}

void MoneyManager::SetIndTax(std::string setInd){
	indTax = atoi(setInd.c_str());
}

int MoneyManager::GetRedTax(void){
	return redTax;
}

int MoneyManager::GetComTax(void){
	return comTax;
}

int MoneyManager::GetIndTax(void){
	return indTax;
}
