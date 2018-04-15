#ifndef WORLD_H_
#define WORLD_H_

#include "Tile.h"
#include "Building.h"
#include "UIManager.h"
#include "MouseManager.h"
#include "MapGenerator.h"
#include "MoneyManager.h"
#include "PopulationManager.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>

class Tile;
class Building;
class BuildingType;
class MapGenerator;

enum class BuildingTypeEnum : unsigned int;

class World {
public:
	World(int setWidth,int setHeight);
	~World(void);

	bool Update(int deltaTime);

	void SetUpWorld(std::string filePath = "maps/0.png");

	void Save(std::string fileName);
	void Load(std::string fileName);

	void ChangeBuilding(BuildingTypeEnum buildingType,int x,int y);

	Tile *GetTileAt(int x, int y);
	Tile *GetTileAtPixels(int x, int y);

	Building *GetBuildingAt(int x, int y);
	Building *GetBuildingAtPixels(int x, int y);

	int GetPowerStatusAt(int x, int y);
	int GetPowerStatusAtPixels(int x, int y);

	int GetFireStatusAt(int x, int y);
	int GetFireStatusAtPixels(int x, int y);

	int GetWidth(void);
	int GetHeight(void);

	bool loadingNew;
private:
	void UpdatePowerMap(BuildingTypeEnum buildingType,int x,int y);
	void ActivatePowerlines(int x,int y);
	void InactivatePowerlines(int x,int y);
	bool ConnectsToPowerplant(int x,int y,std::vector<std::string> doNotInclude);

	void UpdateFireMap(BuildingTypeEnum buildingType,int x,int y);

	int width;
	int height;

	MapGenerator *mapGenerator;

	std::vector<std::vector<Tile>> tiles;

	std::vector<std::vector<Building>> buildings;
	std::vector<int> emptyBuildingsX;
	std::vector<int> emptyBuildingsY;

	std::vector<std::vector<int>> powerMap; //0 = no power; 1 = has power (meaning it is within 5 tiles of a power source); 2 = empty power source (ex: unconnected powerline); 3 = viable power source (ex: connected powerline or powerplant)
	std::vector<std::vector<int>> fireMap; //0 = no fire; 1 = has fire; 2 = burnt ground; 3 = fire station

	int currMonthTime;
	const int monthLength = 10000;
};

#endif
