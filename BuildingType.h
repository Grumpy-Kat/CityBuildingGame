#ifndef BUILDINGTYPE_H_
#define BUILDINGTYPE_H_

#include <string>

enum class BuildingTypeEnum : unsigned int{
	Residential = 0,
	Commercial,
	Industrial,
	Road,
	Powerline,
	CoalPowerplant,
	Fire,
	BurntGround,
	FireStation,
	None
};

class BuildingType{
public:
	BuildingType();
	~BuildingType();

	static std::string EnumToStr(BuildingTypeEnum type,bool spaces = true);

	static BuildingTypeEnum StrToEnum(std::string string);
};

#endif
