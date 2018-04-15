#ifndef MOUSEMANAGER_H_
#define MOUSEMANAGER_H_

#include "SDL_Includes.h"
#include "World.h"
#include "Camera.h"
#include "Building.h"
#include "Sprite.h"
#include "BuildingType.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

class World;
class Camera;
class Sprite;

class MouseManager {
public:
	~MouseManager();

	void Start(void);
	void Update(SDL_Event *event,Camera *camera);

	static MouseManager &GetInstance(void);

	void SetBuildingType(std::string setBuildingType);
private:
	MouseManager();

	void UpdateTileDrag(SDL_Event *event,Camera *camera);
	void UpdateCameraMove(SDL_Event *event,Camera *camera);
	void UpdateCameraZoom(SDL_Event *event,Camera *camera);

	int currMouseX;
	int currMouseY;

	int lastMouseX;
	int lastMouseY;

	int tileDragStartX;
	int tileDragStartY;
	bool isTileDragging;

	bool isCameraMoving;

	std::vector<Sprite> dragPreviews;

	BuildingTypeEnum buildingType;
};

#endif
