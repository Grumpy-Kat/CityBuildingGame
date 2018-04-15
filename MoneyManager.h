#ifndef MONEYMANAGER_H_
#define MONEYMANAGER_H_

#include "MenuManager.h"
#include <map>

class MoneyManager {
public:
	~MoneyManager(void);

	void Start(void);

	static MoneyManager &GetInstance(void);

	void AddAmount(int addAmt);
	int GetAmount(void);

	void TakeLoan(int amount);
	void SubtractLoanInterest(void);
	bool GetLoanInfo(int amount);

	void SetRedTax(std::string setRed);
	void SetComTax(std::string setCom);
	void SetIndTax(std::string setInd);

	int GetRedTax(void);
	int GetComTax(void);
	int GetIndTax(void);
private:
	MoneyManager(void);

	int amt;

	std::map<int,bool> loans;

	int redTax;
	int comTax;
	int indTax;
};

#endif
