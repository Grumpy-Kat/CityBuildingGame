#include "FireManager.h"

FireManager::FireManager(){

}

FireManager::~FireManager(){
}

void FireManager::Start(void){
	timeSinceLastFire = 0;
	timeSinceLastTryFire = 0;
	timeSinceLastSpreadFire = 0;
	fireAble = false;
}

void FireManager::Update(int deltaTime){
	if(!fireAble){
		timeSinceLastFire += deltaTime;
		if(timeSinceLastFire >= 10000){
			timeSinceLastFire = 0;
			fireAble = true;
		}
	}
	if(fireAble){
		if(timeSinceLastTryFire >= 3000){
			timeSinceLastTryFire = 0;
			if(rand()%12 == 0){
				fireAble = false;
				int x = 0, y = 0;
				bool canPlace = false;
				while(!canPlace){
					x = rand()%(WorldManager::GetInstance().GetWorld()->GetWidth()-1);
					y = rand()%(WorldManager::GetInstance().GetWorld()->GetHeight()-1);
					if(WorldManager::GetInstance().GetWorld()->GetTileAt(x,y)->IsPlaceable()){
						canPlace = true;
					}
				}
				WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::Fire,x,y);
				std::vector<int> coord;
				coord.push_back(x);
				coord.push_back(y);
				coords.push_back(coord);
			}
		} else{
			timeSinceLastTryFire += deltaTime;
		}
	}
	if(timeSinceLastSpreadFire >= 1500){
		timeSinceLastSpreadFire = 0;
		if(coords.size() != 0 && rand()%4 == 0){
			std::vector<std::vector<int>> addCoords;
			for(unsigned int i = 0;i < coords.size();i++){
				if(WorldManager::GetInstance().GetWorld()->GetFireStatusAt(coords[i][0],coords[i][1]) == 1){
					int coord[2] = {coords[i][0],coords[i][1]};
					std::vector<int> newCoord;
					newCoord.push_back(coord[0]+1);
					newCoord.push_back(coord[1]);
					if(rand()%2 == 0){
						WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::Fire,newCoord[0],newCoord[1]);
						addCoords.push_back(newCoord);
					}
					newCoord[0] = coord[0]-1;
					newCoord[1] = coord[1];
					if(rand()%2 == 0){
						WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::Fire,newCoord[0],newCoord[1]);
						addCoords.push_back(newCoord);
					}
					newCoord[0] = coord[0];
					newCoord[1] = coord[1]+1;
					if(rand()%2 == 0){
						WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::Fire,newCoord[0],newCoord[1]);
						addCoords.push_back(newCoord);
					}
					newCoord[0] = coord[0];
					newCoord[1] = coord[1]-1;
					if(rand()%2 == 0){
						WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::Fire,newCoord[0],newCoord[1]);
						addCoords.push_back(newCoord);
					}
				} else{
					WorldManager::GetInstance().GetWorld()->ChangeBuilding(BuildingTypeEnum::None,coords[i][0],coords[i][1]);
					coords.erase(coords.begin() + i);
				}
			}
			for(unsigned int i = 0;i < addCoords.size();i++){
				coords.push_back(addCoords[i]);
			}
		}
	} else{
		if(coords.size() > 0){
			timeSinceLastSpreadFire += deltaTime;
		}
	}
}

void FireManager::End(void){
	coords.clear();
}

FireManager &FireManager::GetInstance(void){
	static FireManager *instance = nullptr;
	if(instance == nullptr){
		instance = new FireManager;
	}
	return *instance;
}
