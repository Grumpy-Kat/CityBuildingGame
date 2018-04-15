#include "Building.h"

Building::Building(void){
	world = nullptr;
	type = BuildingTypeEnum::None;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	connectsToNeighbors = false;
	powerlineShown = true;
	containsPowerline = false;
	hasPower = false;
	price = 0 ;
	//creaty empty sprites
	sprites.push_back(Sprite());
	sprites.push_back(Sprite());
	redPop = 0;
	comPop = 0;
	indPop = 0;
}

Building::Building(World *setWorld,int setX,int setY,int setWidth,int setHeight){
	world = setWorld;
	type = BuildingTypeEnum::None;
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	connectsToNeighbors = false;
	powerlineShown = true;
	containsPowerline = false;
	hasPower = false;
	price = 0;
	//create empty sprites
	if(sprites.size() == 0){
		sprites.push_back(Sprite());
		sprites.push_back(Sprite());
	} else{
		sprites[0] = Sprite();
		sprites[0] = Sprite();
	}
	redPop = 0;
	comPop = 0;
	indPop = 0;
}

Building::~Building(void){
}

void Building::UpdateSprite(bool powerline){
	if(powerline){
		if(!powerlineShown){
			return;
		}
		std::string filePath;
		if(type == BuildingTypeEnum::None){
			filePath = "images/PowerlineStanding/" + GetFilePathForBuilding(true) + ".png";
		} else{
			filePath = "images/PowerlineFloating/" + GetFilePathForBuilding(true) + ".png";
		}
		if(sprites.size() == 1){
			sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
		} else{
			sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
		}
	} else{
		std::string filePath = "images/" + BuildingType::EnumToStr(type) + "/" + GetFilePathForBuilding() + ".png";
		if(sprites.size() == 0){
			sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
		} else{
			sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
		}
	}
}

std::string Building::GetFilePathForBuilding(bool powerline){
	std::string spriteName = "_";
	//check for neighbors
	Building *building;
	building = world->GetBuildingAt(x,y+1);
	if(building != nullptr && powerline){
		if(building->GetContainsPowerline()){
			//north neighbor with same building type
			spriteName += "N";
		}
	} else{
		if(building->GetType() == type){
			//north neighbor with same building type
			spriteName += "N";
		}
	}
	building = world->GetBuildingAt(x+1,y);
	if(building != nullptr && powerline){
		if(building->GetContainsPowerline()){
			//east neighbor with same building type
			spriteName += "E";
		}
	} else{
		if(building->GetType() == type){
			//east neighbor with same building type
			spriteName += "E";
		}
	}
	building = world->GetBuildingAt(x,y-1);
	if(building != nullptr && powerline){
		if(building->GetContainsPowerline()){
			//south neighbor with same building type
			spriteName += "S";
		}
	} else{
		if(building->GetType() == type){
			//south neighbor with same building type
			spriteName += "S";
		}
	}
	building = world->GetBuildingAt(x-1,y);
	if(building != nullptr && powerline){
		if(building->GetContainsPowerline()){
			//west neighbor with same building type
			spriteName += "W";
		}
	} else{
		if(building->GetType() == type){
			//west neighbor with same building type
			spriteName += "W";
		}
	}
	return spriteName;
}

void Building::FinishBuilding(std::string filePath){
	std::cout << "FinishBuilding" << std::endl;
	switch(type){
		case BuildingTypeEnum::Residential: {
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			redPop = rand()%10;
			if(PopulationManager::GetInstance().GetRedPool() < redPop){
				redPop = PopulationManager::GetInstance().GetRedPool();
			}
			PopulationManager::GetInstance().AddRedPop(redPop);
			PopulationManager::GetInstance().AddRedPool(-redPop);
			PopulationManager::GetInstance().AddComPool(redPop / 2);
			PopulationManager::GetInstance().AddIndPool(redPop / 2);
			if(sprites[0].GetFilePath() != "images/Residential/Default.png"){
				break;
			}
			if(filePath == ""){
				char randNum = '0' + rand()%9;
				filePath = "images/Residential/" + std::string(1,randNum) + std::string(".png");
			}
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			powerlineShown = false;
			break;
		}
		case BuildingTypeEnum::Commercial: {
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			comPop = rand()%10;
			if(PopulationManager::GetInstance().GetComPool() < comPop){
				comPop = PopulationManager::GetInstance().GetComPool();
			}
			PopulationManager::GetInstance().AddComPop(comPop);
			PopulationManager::GetInstance().AddRedPool(comPop / 2);
			PopulationManager::GetInstance().AddComPool(-comPop);
			PopulationManager::GetInstance().AddIndPool(comPop / 2);
			if(sprites[0].GetFilePath() != "images/Commercial/Default.png"){
				break;
			}
			if(filePath == ""){
				char randNum = '0' + rand()%9;
				filePath = "images/Commercial/" + std::string(1,randNum) + std::string(".png");
			}
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			powerlineShown = false;
			break;
		}
		case BuildingTypeEnum::Industrial: {
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			indPop = rand()%10;
			if(PopulationManager::GetInstance().GetIndPool() < indPop){
				indPop = PopulationManager::GetInstance().GetIndPool();
			}
			PopulationManager::GetInstance().AddIndPop(indPop);
			PopulationManager::GetInstance().AddRedPool(indPop / 2);
			PopulationManager::GetInstance().AddComPool(indPop / 2);
			PopulationManager::GetInstance().AddIndPool(-indPop);
			if(sprites[0].GetFilePath() != "images/Industrial/Default.png"){
				break;
			}
			if(filePath == ""){
				char randNum = '0' + rand()%9;
				filePath = "images/Industrial/" + std::string(1,randNum) + std::string(".png");
			}
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			powerlineShown = false;
			break;
		}
	}
	UpdatePowerline();
}

bool Building::SetType(BuildingTypeEnum newType){
	bool success = true;
	switch(newType){
		case BuildingTypeEnum::Residential: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 200 < -1000){
				success = false;
				break;
			}
			price = 200;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/Residential/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			if(!hasPower){
				std::string filePath = "images/NoPower.png";
				if(sprites.size() == 1){
					sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
				} else{
					sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
				}
			}
			connectsToNeighbors = false;
			powerlineShown = true;
			break;
		}
		case BuildingTypeEnum::Commercial: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 200 < -1000){
				success = false;
				break;
			}
			price = 200;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/Commercial/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			if(!hasPower){
				std::string filePath = "images/NoPower.png";
				if(sprites.size() == 1){
					sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
				} else{
					sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
				}
			}
			connectsToNeighbors = false;
			powerlineShown = true;
			break;
		}
		case BuildingTypeEnum::Industrial: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 200 < -1000){
				success = false;
				break;
			}
			price = 200;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/Industrial/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			if(!hasPower){
				std::string filePath = "images/NoPower.png";
				if(sprites.size() == 1){
					sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
				} else{
					sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
				}
			}
			connectsToNeighbors = false;
			powerlineShown = true;
			break;
		}
		case BuildingTypeEnum::Road: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 50 < -1000){
				success = false;
				break;
			}
			price = 50;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/Road/" + GetFilePathForBuilding() + ".png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			//check for neighbors
			Building *building;
			building = world->GetBuildingAt(x,y-1);
			if(building != nullptr && building->GetType() == type){
				//north neighbor with same building type
				building->UpdateSprite();
			}
			building = world->GetBuildingAt(x+1,y);
			if(building != nullptr && building->GetType() == type){
				//east neighbor with same building type
				building->UpdateSprite();
			}
			building = world->GetBuildingAt(x,y+1);
			if(building != nullptr && building->GetType() == type){
				//south neighbor with same building type
				building->UpdateSprite();
			}
			building = world->GetBuildingAt(x-1,y);
			if(building != nullptr && building->GetType() == type){
				//west neighbor with same building type
				building->UpdateSprite();
			}
			connectsToNeighbors = true;
			powerlineShown = true;
			break;
		}
		case BuildingTypeEnum::Powerline: {
			if(containsPowerline || MoneyManager::GetInstance().GetAmount() - 25 < -1000){
				break;
			}
			price = 25;
			MoneyManager::GetInstance().AddAmount(-price);
			containsPowerline = true;
			break;
		}
		case BuildingTypeEnum::CoalPowerplant: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 750 < -1000){
				success = false;
				break;
			}
			price = 750;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/CoalPowerplant/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			connectsToNeighbors = false;
			powerlineShown = false;
			containsPowerline = true;
			break;
		}
		case BuildingTypeEnum::Fire: {
			if(type == newType){
				success = false;
				break;
			}
			price = 0;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			type = newType;
			std::string filePath = "images/Fire/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"animations"));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"animations");
			}
			connectsToNeighbors = false;
			powerlineShown = false;
			containsPowerline = false;
			break;
		}
		case BuildingTypeEnum::FireStation: {
			if(type == newType || MoneyManager::GetInstance().GetAmount() - 500 < -1000){
				success = false;
				break;
			}
			price = 500;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			type = newType;
			std::string filePath = "images/FireStation/Default.png";
			if(sprites.size() == 0){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height));
			} else{
				sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height);
			}
			connectsToNeighbors = false;
			powerlineShown = false;
			break;
		}
		case BuildingTypeEnum::None: {
			if(MoneyManager::GetInstance().GetAmount() - 10 < -1000){
				success = false;
				break;
			}
			if(type == newType){
				if(containsPowerline){
					MoneyManager::GetInstance().AddAmount(-10);
					containsPowerline = false;
				}
				break;
			}
			price = 10;
			//clear values
			PopulationManager::GetInstance().AddRedPop(-redPop);
			redPop = 0;
			PopulationManager::GetInstance().AddComPop(-comPop);
			comPop = 0;
			PopulationManager::GetInstance().AddIndPop(-indPop);
			indPop = 0;
			//set values
			MoneyManager::GetInstance().AddAmount(-price);
			if(sprites.size() > 0){
				SpriteManager::GetInstance().RemoveSprite(sprites[0]);
				sprites[0] = Sprite();
			}
			BuildingTypeEnum prevType = type;
			type = newType;
			if(connectsToNeighbors){
				//check for neighbors
				Building *building;
				building = world->GetBuildingAt(x,y-1);
				if(building != nullptr && building->GetType() == prevType){
					//north neighbor with same building type
					building->UpdateSprite();
				}
				building = world->GetBuildingAt(x+1,y);
				if(building != nullptr && building->GetType() == prevType){
					//east neighbor with same building type
					building->UpdateSprite();
				}
				building = world->GetBuildingAt(x,y+1);
				if(building != nullptr && building->GetType() == prevType){
					//south neighbor with same building type
					building->UpdateSprite();
				}
				building = world->GetBuildingAt(x-1,y);
				if(building != nullptr && building->GetType() == prevType){
					//west neighbor with same building type
					building->UpdateSprite();
				}
			}
			connectsToNeighbors = false;
			powerlineShown = true;
			containsPowerline = false;
			break;
		}
	}
	UpdatePowerline();
	return success;
}

void Building::UpdatePowerline(void){
	//check for neighbors
	Building *building;
	building = world->GetBuildingAt(x,y-1);
	if(building != nullptr && building->GetContainsPowerline()){
		//north neighbor with same building type
		building->UpdateSprite(true);
	}
	building = world->GetBuildingAt(x+1,y);
	if(building != nullptr && building->GetContainsPowerline()){
		//east neighbor with same building type
		building->UpdateSprite(true);
	}
	building = world->GetBuildingAt(x,y+1);
	if(building != nullptr && building->GetContainsPowerline()){
		//south neighbor with same building type
		building->UpdateSprite(true);
	}
	building = world->GetBuildingAt(x-1,y);
	if(building != nullptr && building->GetContainsPowerline()){
		//west neighbor with same building type
		building->UpdateSprite(true);
	}
	if(!hasPower && (type == BuildingTypeEnum::Residential || type == BuildingTypeEnum::Commercial || type == BuildingTypeEnum::Industrial)){
		return;
	}
	if(!containsPowerline && hasPower && sprites.size() > 1){
		SpriteManager::GetInstance().RemoveSprite(sprites[1],"overlays");
		//make empty sprite
		sprites[1] = Sprite();
		return;
	}
	if(!containsPowerline && !hasPower && (type != BuildingTypeEnum::Residential || type != BuildingTypeEnum::Commercial || type != BuildingTypeEnum::Industrial) && sprites.size() > 1){
		SpriteManager::GetInstance().RemoveSprite(sprites[1],"overlays");
		//make empty sprite
		sprites[1] = Sprite();
		return;
	}
	if(!powerlineShown && hasPower && sprites.size() > 1){
		SpriteManager::GetInstance().RemoveSprite(sprites[1],"overlays");
		//make empty sprite
		sprites[1] = Sprite();
		return;
	}
	//powerline is shown
	std::string filePath;
	if(type == BuildingTypeEnum::None){
		filePath = "images/PowerlineStanding/" + GetFilePathForBuilding(true) + ".png";
	} else{
		filePath = "images/PowerlineFloating/" + GetFilePathForBuilding(true) + ".png";
	}
	if(sprites.size() == 1){
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
	} else{
		sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
	}
}

BuildingTypeEnum Building::GetType(void){
	return type;
}

int Building::GetX(void){
	return x;
}

int Building::GetY(void){
	return y;
}

int Building::GetWidth(void){
	return width;
}

int Building::GetHeight(void){
	return height;
}

bool Building::GetConnectsToNeighbors(void){
	return connectsToNeighbors;
}

bool Building::GetContainsPowerline(void){
	return containsPowerline;
}

void Building::SetHasPower(bool setHasPower){
	if(hasPower == setHasPower){
		return;
	}
	hasPower = setHasPower;
	if(!hasPower){
		if(type == BuildingTypeEnum::Residential || type == BuildingTypeEnum::Commercial || type == BuildingTypeEnum::Industrial){
			std::string filePath = "images/NoPower.png";
			if(sprites.size() == 1){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * 24,y * 24,width,height,"overlays"));
			} else{
				sprites[1] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * 24,y * 24,width,height,"overlays");
			}

		} else if(sprites[1].GetFilePath() == "images/NoPower.png"){
			SpriteManager::GetInstance().RemoveSprite(sprites[1],"overlays");
			sprites[1] = Sprite();
		}
		//clear values
		PopulationManager::GetInstance().AddRedPop(-redPop);
		PopulationManager::GetInstance().AddRedPool(redPop);
		redPop = 0;
		PopulationManager::GetInstance().AddComPop(-comPop);
		PopulationManager::GetInstance().AddComPool(comPop);
		comPop = 0;
		PopulationManager::GetInstance().AddIndPop(-indPop);
		PopulationManager::GetInstance().AddIndPool(indPop);
		indPop = 0;
	} else{
		if(sprites[1].GetFilePath() == "images/NoPower.png"){
			SpriteManager::GetInstance().RemoveSprite(sprites[1],"overlays");
			sprites[1] = Sprite();
		}
	}
}

bool Building::GetHasPower(void){
	return hasPower;
}

int Building::GetPrice(void){
	return price;
}

Sprite Building::GetSprite(void){
	return sprites[0];
}

void Building::SetRedPop(int setRedPop){
	redPop = setRedPop;
	PopulationManager::GetInstance().AddRedPop(redPop);
}

void Building::SetComPop(int setComPop){
	comPop = setComPop;
	PopulationManager::GetInstance().AddComPop(comPop);
}

void Building::SetIndPop(int setIndPop){
	indPop = setIndPop;
	PopulationManager::GetInstance().AddIndPop(indPop);
}

int Building::GetRedPop(void){
	return redPop;
}

int Building::GetComPop(void){
	return comPop;
}

int Building::GetIndPop(void){
	return indPop;
}
