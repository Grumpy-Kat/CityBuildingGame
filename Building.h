#ifndef BUILDING_H_
#define BUILDING_H_

#include "Sprite.h"
#include "World.h"
#include "BuildingType.h"
#include "MoneyManager.h"
#include "PopulationManager.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

class World;

class Building {
public:
	Building(void);
	Building(World *setWorld,int setX,int setY,int setWidth = 24,int setHeight = 24);
	~Building(void);

	void UpdateSprite(bool powerline = false);

	std::string GetFilePathForBuilding(bool powerline = false);

	void FinishBuilding(std::string filePath = "");

	bool SetType(BuildingTypeEnum newType);
	BuildingTypeEnum GetType(void);

	int GetX(void);
	int GetY(void);
	int GetWidth(void);
	int GetHeight(void);

	bool GetConnectsToNeighbors(void);
	bool GetContainsPowerline(void);
	void SetHasPower(bool setHasPower);
	bool GetHasPower(void);

	int GetPrice(void);

	Sprite GetSprite(void);

	void SetRedPop(int setRedPop);
	void SetComPop(int setComPop);
	void SetIndPop(int setIndPop);

	int GetRedPop(void);
	int GetComPop(void);
	int GetIndPop(void);
private:
	void UpdatePowerline(void);

	World *world;

	BuildingTypeEnum type;

	int x;
	int y;
	int width;
	int height;

	bool connectsToNeighbors;
	bool powerlineShown;
	bool containsPowerline;
	bool hasPower;

	int price;

	std::vector<Sprite> sprites;

	int redPop;
	int comPop;
	int indPop;
};

#endif
