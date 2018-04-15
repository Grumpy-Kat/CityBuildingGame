#include "BuildingType.h"

BuildingType::BuildingType(){
}

BuildingType::~BuildingType(){
}

std::string BuildingType::EnumToStr(BuildingTypeEnum type,bool spaces){
	switch(type){
		case BuildingTypeEnum::Residential: {
			return "Residential";
		}
		case BuildingTypeEnum::Commercial: {
			return "Commercial";
		}
		case BuildingTypeEnum::Industrial: {
			return "Industrial";
		}
		case BuildingTypeEnum::Road: {
			return "Road";
		}
		case BuildingTypeEnum::Powerline: {
			return "Powerline";
		}
		case BuildingTypeEnum::CoalPowerplant: {
			if(spaces){
				return "Coal Powerplant";
			} else{
				return "CoalPowerplant";
			}
		}
		case BuildingTypeEnum::Fire: {
			return "Fire";
		}
		case BuildingTypeEnum::BurntGround: {
			if(spaces){
				return "Burnt Ground";
			} else{
				return "BurntGround";
			}
		}
		case BuildingTypeEnum::FireStation: {
			if(spaces){
				return "Fire Station";
			} else{
				return "FireStation";
			}
		}
		case BuildingTypeEnum::None: {
			return "None";
		}
		default: {
			return "None";
		}
	}
}

BuildingTypeEnum BuildingType::StrToEnum(std::string string){
	if(string == "Residential"){
		return BuildingTypeEnum::Residential;
	}
	if(string == "Commercial"){
		return BuildingTypeEnum::Commercial;
	}
	if(string == "Industrial"){
		return BuildingTypeEnum::Industrial;
	}
	if(string == "Road"){
		return BuildingTypeEnum::Road;
	}
	if(string == "Powerline"){
		return BuildingTypeEnum::Powerline;
	}
	if(string == "Coal Powerplant" || string == "CoalPowerplant"){
		return BuildingTypeEnum::CoalPowerplant;
	}
	if(string == "Fire"){
		return BuildingTypeEnum::Fire;
	}
	if(string == "Burnt Ground" || string == "BurntGround"){
		return BuildingTypeEnum::BurntGround;
	}
	if(string == "Fire Station" || string == "FireStation"){
		return BuildingTypeEnum::FireStation;
	}
	return BuildingTypeEnum::None;
}
