#ifndef POPULATIONMANAGER_H_
#define POPULATIONMANAGER_H_

#include "MenuManager.h"

class PopulationManager {
public:
	~PopulationManager(void);

	void Start(void);

	static PopulationManager &GetInstance(void);

	void AddRedPop(int addPop);
	void AddComPop(int addPop);
	void AddIndPop(int addPop);

	int GetRedPop(void);
	int GetComPop(void);
	int GetIndPop(void);

	void AddRedPool(int addPool);
	void AddComPool(int addPool);
	void AddIndPool(int addPool);

	int GetRedPool(void);
	int GetComPool(void);
	int GetIndPool(void);
private:
	PopulationManager(void);

	int redPop;
	int comPop;
	int indPop;

	int redPool;
	int comPool;
	int indPool;
};

#endif
