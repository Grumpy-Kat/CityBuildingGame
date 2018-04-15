#include "World.h"

World::World(int setWidth,int setHeight){
	width = setWidth;
	height = setHeight;
	currMonthTime = 0;
	loadingNew = false;
	mapGenerator = new MapGenerator();
}

World::~World(void){
}

bool World::Update(int deltaTime){
	currMonthTime += deltaTime;
	if(currMonthTime >= monthLength){
		MoneyManager::GetInstance().AddAmount(PopulationManager::GetInstance().GetRedPop() * MoneyManager::GetInstance().GetRedTax());
		MoneyManager::GetInstance().AddAmount(PopulationManager::GetInstance().GetComPop() * MoneyManager::GetInstance().GetComTax());
		MoneyManager::GetInstance().AddAmount(PopulationManager::GetInstance().GetIndPop() * MoneyManager::GetInstance().GetIndTax());
		MoneyManager::GetInstance().SubtractLoanInterest();
		if(emptyBuildingsX.size() > 0){
			int size = emptyBuildingsX.size();
			if(size > 50){
				size = 50;
			}
			for(int i = 0;i < size;i++){
				if(buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() != BuildingTypeEnum::Residential && buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() != BuildingTypeEnum::Commercial && buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() != BuildingTypeEnum::Industrial){
					emptyBuildingsX.erase(emptyBuildingsX.begin() + 0);
					emptyBuildingsY.erase(emptyBuildingsY.begin() + 0);
				}
				if(powerMap[emptyBuildingsX[0]][emptyBuildingsY[0]] != 0){
					buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].SetHasPower(true);
					if(buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() == BuildingTypeEnum::Residential && PopulationManager::GetInstance().GetRedPool() > 0){
						buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].FinishBuilding();
						emptyBuildingsX.erase(emptyBuildingsX.begin() + 0);
						emptyBuildingsY.erase(emptyBuildingsY.begin() + 0);
					}
					if(buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() == BuildingTypeEnum::Commercial && PopulationManager::GetInstance().GetComPool() > 0){
						buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].FinishBuilding();
						emptyBuildingsX.erase(emptyBuildingsX.begin() + 0);
						emptyBuildingsY.erase(emptyBuildingsY.begin() + 0);
					}
					if(buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].GetType() == BuildingTypeEnum::Industrial && PopulationManager::GetInstance().GetIndPool() > 0){
						buildings[emptyBuildingsX[0]][emptyBuildingsY[0]].FinishBuilding();
						emptyBuildingsX.erase(emptyBuildingsX.begin() + 0);
						emptyBuildingsY.erase(emptyBuildingsY.begin() + 0);
					}
				}
			}
		}
		PopulationManager::GetInstance().AddRedPool(100);
		PopulationManager::GetInstance().AddComPool(100);
		PopulationManager::GetInstance().AddIndPool(100);
		currMonthTime = 0;
	}
	if(loadingNew){
		return true;
	}
	return false;
}

void World::SetUpWorld(std::string filePath){
	mapGenerator->Load(filePath);
	for (int x = 0; x < width; x++) {
		std::vector<Tile> subTileVector;
		std::vector<Building> subBuildingVector;
		std::vector<int> subPowerMapVector;
		std::vector<int> subFireMapVector;
		for (int y = 0; y < height; y++) {
			int terrainHeightTile = mapGenerator->city[y][x];
			subTileVector.push_back(Tile(this,x,y,terrainHeightTile));
			subBuildingVector.push_back(Building(this,x,y));
			subPowerMapVector.push_back(0);
			subFireMapVector.push_back(0);
		}
		tiles.push_back(subTileVector);
		buildings.push_back(subBuildingVector);
		powerMap.push_back(subPowerMapVector);
		fireMap.push_back(subFireMapVector);
	}
}

void World::Save(std::string fileName){
	std::cout << "Save: " << fileName << std::endl;
	std::ofstream file;
	file.open(fileName,std::ofstream::trunc | std::ofstream::out);
	file << "money=" << MoneyManager::GetInstance().GetAmount() << std::endl;
	file << "1000Loan=" << MoneyManager::GetInstance().GetLoanInfo(1000) << std::endl;
	file << "5000Loan=" << MoneyManager::GetInstance().GetLoanInfo(5000) << std::endl;
	file << "10000Loan=" << MoneyManager::GetInstance().GetLoanInfo(10000) << std::endl;
	file << "25000Loan=" << MoneyManager::GetInstance().GetLoanInfo(25000) << std::endl;
	file << "100000Loan=" << MoneyManager::GetInstance().GetLoanInfo(100000) << std::endl;
	file << "500000Loan=" << MoneyManager::GetInstance().GetLoanInfo(500000) << std::endl;
	file << "redTax=" << MoneyManager::GetInstance().GetRedTax() << std::endl;
	file << "comTax=" << MoneyManager::GetInstance().GetComTax() << std::endl;
	file << "indTax=" << MoneyManager::GetInstance().GetIndTax() << std::endl;
	file << "redPool=" << PopulationManager::GetInstance().GetRedPool() << std::endl;
	file << "comPool=" << PopulationManager::GetInstance().GetComPool() << std::endl;
	file << "indPool=" << PopulationManager::GetInstance().GetIndPool() << std::endl;
	file << std::endl << "TILES_BEGIN" << std::endl;
	for(int x = 0;x < width;x++){
		for(int y = 0;y < height;y++){
			if(tiles[x][y].GetSprite().GetFilePath() != "images/Tile/WaterTile.png"){
				file << "x=" << x << " y=" << y << " filePath=" << tiles[x][y].GetSprite().GetFilePath() << std::endl;
			}
		}
	}
	file << "TILES_END" << std::endl;
	file << std::endl << "BUILDINGS_BEGIN" << std::endl;
	for(int x = 0;x < width;x++){
		for(int y = 0;y < height;y++){
			if(buildings[x][y].GetType() != BuildingTypeEnum::None || buildings[x][y].GetContainsPowerline()){
				file << "x=" << x << " y=" << y << " filePath=" << buildings[x][y].GetSprite().GetFilePath() << " type=" << BuildingType::EnumToStr(buildings[x][y].GetType(),false) << " containsPowerline=" << buildings[x][y].GetContainsPowerline() << " redPop=" << buildings[x][y].GetRedPop() << " comPop=" << buildings[x][y].GetComPop() << " indPop=" << buildings[x][y].GetIndPop() << std::endl;
			}
		}
	}
	file << "BUILDINGS_END" << std::endl;
	file.close();
}

void World::Load(std::string fileName){
	std::ifstream file(fileName);
	std::string line;
	enum LineType : unsigned int {
		Various = 0,
		Tiles,
		Buildings
	};
	LineType currType = Various;
	if(file.is_open()){
		for (int x = 0; x < width; x++) {
			std::vector<int> subPowerMapVector;
			for (int y = 0; y < height; y++) {
				subPowerMapVector.push_back(0);
			}
			powerMap.push_back(subPowerMapVector);
		}
		while(file.good()){
			std::getline(file,line);
			if(line != ""){
				if(line == "TILES_BEGIN"){
					currType = Tiles;
					for (int x = 0; x < width; x++) {
						std::vector<Tile> subTileVector;
						for (int y = 0; y < height; y++) {
							subTileVector.push_back(Tile(this,x,y,0));
						}
						tiles.push_back(subTileVector);
					}
				} else if(line == "BUILDINGS_BEGIN"){
					currType = Buildings;
					for (int x = 0; x < width; x++) {
						std::vector<Building> subBuildingVector;
						for (int y = 0; y < height; y++) {
							subBuildingVector.push_back(Building(this,x,y));
						}
						buildings.push_back(subBuildingVector);
					}
				} else if(line == "TILES_END"){
					currType = Various;
				} else if(line == "BUILDINGS_END"){
					currType = Various;
				} else{
					//info to load
					std::string key;
					std::string value;
					std::string pair;
					if(currType == Various){
						key = line.substr(0,line.find("="));
						value = line.substr(line.find("=") + 1,line.size());
						if(key == "money"){
							MoneyManager::GetInstance().AddAmount(-MoneyManager::GetInstance().GetAmount());
							MoneyManager::GetInstance().AddAmount(atoi(value.c_str()));
						}
						if(key == "1000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(1000);
								MoneyManager::GetInstance().AddAmount(-1000);
							}
						}
						if(key == "5000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(5000);
								MoneyManager::GetInstance().AddAmount(-5000);
							}
						}
						if(key == "10000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(10000);
								MoneyManager::GetInstance().AddAmount(-10000);
							}
						}
						if(key == "25000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(25000);
								MoneyManager::GetInstance().AddAmount(-25000);
							}
						}
						if(key == "100000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(100000);
								MoneyManager::GetInstance().AddAmount(-100000);
							}
						}
						if(key == "500000Loan"){
							if(value == "1"){
								MoneyManager::GetInstance().TakeLoan(500000);
								MoneyManager::GetInstance().AddAmount(-500000);
							}
						}
						if(key == "redTax"){
							MoneyManager::GetInstance().SetRedTax(value);
						}
						if(key == "comTax"){
							MoneyManager::GetInstance().SetComTax(value);
						}
						if(key == "indTax"){
							MoneyManager::GetInstance().SetIndTax(value);
						}
						if(key == "redPool"){
							PopulationManager::GetInstance().AddRedPool(-PopulationManager::GetInstance().GetRedPool());
							PopulationManager::GetInstance().AddRedPool(atoi(value.c_str()));
						}
						if(key == "comPool"){
							PopulationManager::GetInstance().AddComPool(-PopulationManager::GetInstance().GetComPool());
							PopulationManager::GetInstance().AddComPool(atoi(value.c_str()));
						}
						if(key == "indPool"){
							PopulationManager::GetInstance().AddIndPool(-PopulationManager::GetInstance().GetIndPool());
							PopulationManager::GetInstance().AddIndPool(atoi(value.c_str()));
						}
					}
					if(currType == Tiles){
						size_t pos = 0;
						int x = 0,y = 0,terrainType = 0;
						while (line.size() > 0) {
							if(line.find(" ") == std::string::npos){
								pos = line.size();
							} else{
								pos = line.find(" ");
							}
							pair = line.substr(0,pos);
							key = pair.substr(0,pair.find("="));
							value = pair.substr(pair.find("=")+1,pair.size()-1);
							if(key == "x"){
								x = atoi(value.c_str());
							}
							if(key == "y"){
								y = atoi(value.c_str());
							}
							if(key == "filePath"){
								if(value == "images/Tile/GrassTile.png"){
									terrainType = 1;
								}
								if(value == "images/Tile/DirtTile.png"){
									terrainType = 2;
								}
							}
						    line.erase(0,pos+1);
						}
						tiles[x][y] = Tile(this,x,y,terrainType);
					}
					if(currType == Buildings){
						size_t pos = 0;
						int x = 0,y = 0;
						std::string filePath = "",type = "";
						int redPop = 0,comPop = 0,indPop = 0;
						bool containsPowerline = false;
						while (line.size() > 0) {
							if(line.find(" ") == std::string::npos){
								pos = line.size();
							} else{
								pos = line.find(" ");
							}
							pair = line.substr(0,pos);
							key = pair.substr(0,pair.find("="));
							value = pair.substr(pair.find("=")+1,pair.size()-1);
							if(key == "x"){
								x = atoi(value.c_str());
							}
							if(key == "y"){
								y = atoi(value.c_str());
							}
							if(key == "filePath"){
								if(value.find("Residential") != std::string::npos && value != "images/Residential/Default.png"){
									filePath = value;
								} else if(value.find("Commercial") != std::string::npos && value != "images/Commercial/Default.png"){
									filePath = value;
								} else if(value.find("Industrial") != std::string::npos && value != "images/Industrial/Default.png"){
									filePath = value;
								}
							}
							if(key == "type"){
								type = value;
							}
							if(key == "containsPowerline"){
								if(value == "1"){
									containsPowerline = true;
								}
							}
							if(key == "redPop"){
								redPop = atoi(value.c_str());
							}
							if(key == "comPop"){
								comPop = atoi(value.c_str());
							}
							if(key == "indPop"){
								indPop = atoi(value.c_str());
							}
						    line.erase(0,pos+1);
						}
						buildings[x][y].SetType(BuildingType::StrToEnum(type));
						MoneyManager::GetInstance().AddAmount(buildings[x][y].GetPrice());
						if(containsPowerline){
							buildings[x][y].SetType(BuildingTypeEnum::Powerline);
							MoneyManager::GetInstance().AddAmount(buildings[x][y].GetPrice());
						}
						if(filePath != ""){
							buildings[x][y].FinishBuilding(filePath);
						}
						buildings[x][y].SetRedPop(buildings[x][y].GetRedPop());
						buildings[x][y].SetRedPop(redPop);
						buildings[x][y].SetComPop(buildings[x][y].GetComPop());
						buildings[x][y].SetComPop(comPop);
						buildings[x][y].SetIndPop(buildings[x][y].GetIndPop());
						buildings[x][y].SetIndPop(indPop);
					}
				}
			}
		}
	}
	std::cout << "Load: Finished loading" << std::endl;
}

void World::ChangeBuilding(BuildingTypeEnum buildingType,int x,int y){
	if(buildingType == BuildingTypeEnum::Powerline || buildingType == BuildingTypeEnum::Road){
		//adding powerline overlay or road (which can be placed over any terrain)
		if(buildings[x][y].SetType(buildingType)){
			UpdatePowerMap(buildingType,x,y);
			UpdateFireMap(buildingType,x,y);
		}
		return;
	}
	if(tiles[x][y].IsPlaceable() && (buildingType == BuildingTypeEnum::Fire || buildingType == BuildingTypeEnum::BurntGround)){
		//adding fire animation
		if(buildings[x][y].SetType(buildingType)){
			UpdateFireMap(buildingType,x,y);
		}
		return;
	}
	if((buildings[x][y].GetType() != BuildingTypeEnum::None || buildings[x][y].GetContainsPowerline()) && buildingType == BuildingTypeEnum::None){
		//bulldozing
		if(buildings[x][y].SetType(buildingType)){
			UpdatePowerMap(buildingType,x,y);
			UpdateFireMap(buildingType,x,y);
		}
		return;
	}
	if(tiles[x][y].IsPlaceable() && buildings[x][y].GetType() == BuildingTypeEnum::None){
		if(buildings[x][y].SetType(buildingType)){
			UpdatePowerMap(buildingType,x,y);
			UpdateFireMap(buildingType,x,y);
			emptyBuildingsX.push_back(x);
			emptyBuildingsY.push_back(y);
		}
	}
}

Tile *World::GetTileAt(int x, int y){
	if(x >= width || x < 0 || y >= height || y < 0){
		return nullptr;
	}
	return &tiles[x][y];
}

Tile *World::GetTileAtPixels(int x, int y){
	if(x >= width*24*WindowManager::GetInstance().GetTileWidthTiles() || x < 0 || y >= height*24*WindowManager::GetInstance().GetTileHeightTiles() || y < 0){
		return nullptr;
	}
	return &tiles[x/24/WindowManager::GetInstance().GetTileWidthTiles()][y/32/WindowManager::GetInstance().GetTileHeightTiles()];
}

Building *World::GetBuildingAt(int x, int y){
	if(x >= width || x < 0 || y >= height || y < 0){
		return nullptr;
	}
	return &buildings[x][y];
}

Building *World::GetBuildingAtPixels(int x, int y){
	if(x >= width*24*WindowManager::GetInstance().GetTileWidthTiles() || x < 0 || y >= height*24*WindowManager::GetInstance().GetTileHeightTiles() || y < 0){
		return nullptr;
	}
	return &buildings[x/24/WindowManager::GetInstance().GetTileWidthTiles()][y/32/WindowManager::GetInstance().GetTileHeightTiles()];
}

int World::GetPowerStatusAt(int x, int y){
	if(x >= width || x < 0 || y >= height || y < 0){
		return -1;
	}
	return powerMap[x][y];
}

int World::GetPowerStatusAtPixels(int x, int y){
	if(x >= width*24*WindowManager::GetInstance().GetTileWidthTiles() || x < 0 || y >= height*24*WindowManager::GetInstance().GetTileHeightTiles() || y < 0){
		return -1;
	}
	return powerMap[x/24/WindowManager::GetInstance().GetTileWidthTiles()][y/32/WindowManager::GetInstance().GetTileHeightTiles()];
}

int World::GetFireStatusAt(int x, int y){
	if(x >= width || x < 0 || y >= height || y < 0){
		return -1;
	}
	std::cout << "GetFireStatusAt " << x << " " << y << " " << fireMap[x][y] << std::endl;
	return fireMap[x][y];
}

int World::GetFireStatusAtPixels(int x, int y){
	if(x >= width*24*WindowManager::GetInstance().GetTileWidthTiles() || x < 0 || y >= height*24*WindowManager::GetInstance().GetTileHeightTiles() || y < 0){
		return -1;
	}
	return fireMap[x/24/WindowManager::GetInstance().GetTileWidthTiles()][y/32/WindowManager::GetInstance().GetTileHeightTiles()];
}

void World::UpdatePowerMap(BuildingTypeEnum buildingType,int x,int y){
	if(buildingType == BuildingTypeEnum::Powerline){
		powerMap[x][y] = 2;
		//see if powerline is connected
		if(powerMap[x + 1][y] == 3 || powerMap[x - 1][y] == 3 || powerMap[x][y + 1] == 3 || powerMap[x][y - 1] == 3){
			//update connections recursively
			ActivatePowerlines(x,y);
		}
	}
	if(buildingType == BuildingTypeEnum::CoalPowerplant){
		//update connections recursively
		ActivatePowerlines(x,y);
	}
	if(buildingType == BuildingTypeEnum::None){
		//powerline bulldozed
		powerMap[x][y] = 0;
		buildings[x][y].SetHasPower(true);
		if((std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x) == emptyBuildingsX.end() && std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y) == emptyBuildingsY.end()) || std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x) != std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y)){
			emptyBuildingsX.push_back(x);
			emptyBuildingsY.push_back(y);
		}
		//update connections recursively
		if(powerMap[x+1][y] == 3 && !ConnectsToPowerplant(x+1,y,std::vector<std::string>(1,std::string("west")))){
			InactivatePowerlines(x+1,y);
		}
		if(powerMap[x-1][y] == 3 && !ConnectsToPowerplant(x-1,y,std::vector<std::string>(1,std::string("east")))){
			InactivatePowerlines(x-1,y);
		}
		if(powerMap[x][y+1] == 3 && !ConnectsToPowerplant(x,y+1,std::vector<std::string>(1,std::string("south")))){
			InactivatePowerlines(x,y+1);
		}
		if(powerMap[x][y-1] == 3 && !ConnectsToPowerplant(x,y-1,std::vector<std::string>(1,std::string("north")))){
			InactivatePowerlines(x,y-1);
		}
		//check if any buildings within 5 tiles don't have power
		for(int i = -5;i <= 5;i++){
			for(int j = -5;j <= 5;j++){
				if(powerMap[x + i][y + j] == 1){
					powerMap[x + i][y + j] = 0;
					buildings[x + i][y + j].SetHasPower(false);
					if((std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x + i) == emptyBuildingsX.end() && std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y + j) == emptyBuildingsY.end()) || std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x + i) != std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y + j)){
						emptyBuildingsX.push_back(x + i);
						emptyBuildingsY.push_back(y + j);
					}
				}
			}
		}
	}
	//update connections recursively
	if(powerMap[x+1][y] == 3){
		ActivatePowerlines(x+1,y);
	}
	if(powerMap[x-1][y] == 3){
		ActivatePowerlines(x-1,y);
	}
	if(powerMap[x][y+1] == 3){
		ActivatePowerlines(x,y+1);
	}
	if(powerMap[x][y-1] == 3){
		ActivatePowerlines(x,y-1);
	}
}

void World::ActivatePowerlines(int x,int y){
	//powerline connected to powerplant or connected powerline
	powerMap[x][y] = 3;
	buildings[x][y].SetHasPower(true);
	if(powerMap[x+1][y] == 2){
		ActivatePowerlines(x+1,y);
	}
	if(powerMap[x-1][y] == 2){
		ActivatePowerlines(x-1,y);
	}
	if(powerMap[x][y+1] == 2){
		ActivatePowerlines(x,y+1);
	}
	if(powerMap[x][y-1] == 2){
		ActivatePowerlines(x,y-1);
	}
	//check if any buildings within 5 tiles don't have power
	for(int i = -5;i <= 5;i++){
		for(int j = -5;j <= 5;j++){
			if(powerMap[x + i][y + j] == 0){
				powerMap[x + i][y + j] = 1;
				buildings[x + i][y + j].SetHasPower(true);
			}
		}
	}
}

void World::InactivatePowerlines(int x,int y){
	powerMap[x][y] = 2;
	buildings[x][y].SetHasPower(false);
	if((std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x) == emptyBuildingsX.end() && std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y) == emptyBuildingsY.end()) || std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x) != std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y)){
		emptyBuildingsX.push_back(x);
		emptyBuildingsY.push_back(y);
	}
	//powerline bulldozed
	if(powerMap[x+1][y] == 3){
		InactivatePowerlines(x+1,y);
	}
	if(powerMap[x-1][y] == 3){
		InactivatePowerlines(x-1,y);
	}
	if(powerMap[x][y+1] == 3){
		InactivatePowerlines(x,y+1);
	}
	if(powerMap[x][y-1] == 3){
		InactivatePowerlines(x,y-1);
	}
	//check if any buildings within 5 tiles have power
	for(int i = -5;i <= 5;i++){
		for(int j = -5;j <= 5;j++){
			if(powerMap[x + i][y + j] == 1){
				powerMap[x + i][y + j] = 0;
				buildings[x + i][y + j].SetHasPower(false);
				if((std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x + i) == emptyBuildingsX.end() && std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y + j) == emptyBuildingsY.end()) || std::find(emptyBuildingsX.begin(),emptyBuildingsX.end(),x + i) != std::find(emptyBuildingsY.begin(),emptyBuildingsY.end(),y + j)){
					emptyBuildingsX.push_back(x + i);
					emptyBuildingsY.push_back(y + j);
				}
			}
		}
	}
}

bool World::ConnectsToPowerplant(int x,int y,std::vector<std::string> doNotInclude){
	if(buildings[x][y].GetType() == BuildingTypeEnum::CoalPowerplant){
		return true;
	}
	if(powerMap[x+1][y] == 3 && std::find(doNotInclude.begin(),doNotInclude.end(),"east") == doNotInclude.end()) {
		if(ConnectsToPowerplant(x+1,y,std::vector<std::string>(1,std::string("west")))){
			return true;
		}
	}
	if(powerMap[x-1][y] == 3 && std::find(doNotInclude.begin(),doNotInclude.end(),"west") == doNotInclude.end()) {
		if(ConnectsToPowerplant(x-1,y,std::vector<std::string>(1,std::string("east")))){
			return true;
		}
	}
	if(powerMap[x][y+1] == 3 && std::find(doNotInclude.begin(),doNotInclude.end(),"north") == doNotInclude.end()) {
		if(ConnectsToPowerplant(x,y+1,std::vector<std::string>(1,std::string("south")))){
			return true;
		}
	}
	if(powerMap[x][y-1] == 3 && std::find(doNotInclude.begin(),doNotInclude.end(),"south") == doNotInclude.end()) {
		if(ConnectsToPowerplant(x,y-1,std::vector<std::string>(1,std::string("north")))){
			return true;
		}
	}
	return (buildings[x][y].GetType() == BuildingTypeEnum::CoalPowerplant);
}

void World::UpdateFireMap(BuildingTypeEnum buildingType,int x,int y){
	if(buildingType == BuildingTypeEnum::Fire){
		fireMap[x][y] = 1;
	}
	if(buildingType == BuildingTypeEnum::BurntGround){
		fireMap[x][y] = 2;
	}
	if(buildingType == BuildingTypeEnum::FireStation){
		fireMap[x][y] = 3;
	}
	if(buildingType == BuildingTypeEnum::None){
		//fire bulldozed
		fireMap[x][y] = 0;
	}
}
int World::GetWidth(void){
	return width;
}

int World::GetHeight(void){
	return height;
}
