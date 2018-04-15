#include "MouseManager.h"

MouseManager::MouseManager() {
}

MouseManager::~MouseManager() {
}

void MouseManager::Start(void){
	currMouseX = 0;
	currMouseY = 0;
	lastMouseX = 0;
	lastMouseY = 0;
	tileDragStartX = 0;
	tileDragStartY = 0;
	isTileDragging = false;
	isCameraMoving = false;
	buildingType = BuildingTypeEnum::None;
}

void MouseManager::Update(SDL_Event *event,Camera *camera){
	if(WindowManager::GetInstance().GetWindow(0)->GetIsMouseFocused()){
		//current pos of mouse
		SDL_GetMouseState(&currMouseX,&currMouseY);
		//handle mouse events
		UpdateCameraMove(event,camera);
		UpdateCameraZoom(event,camera);
		UpdateTileDrag(event,camera);
		//save pos of screen in world
		SDL_GetMouseState(&lastMouseX,&lastMouseY);
	}
}

MouseManager &MouseManager::GetInstance(){
	static MouseManager *instance = nullptr;
	if(instance == nullptr){
		instance = new MouseManager;
	}
	return *instance;
}

void MouseManager::SetBuildingType(std::string setBuildingType){
	buildingType = BuildingType::StrToEnum(setBuildingType);
}

void MouseManager::UpdateTileDrag(SDL_Event *event,Camera *camera){
	if(UIManager::GetInstance().IsOverUI(currMouseX,currMouseY) && !isTileDragging){
		return;
	}
	currMouseX = round((currMouseX) / (24 / camera->GetZoom()) + (camera->GetX() / 24));
	currMouseY = round((currMouseY) / (24 / camera->GetZoom()) + (camera->GetY() / 24));
	if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
		tileDragStartX = currMouseX;
		tileDragStartY = currMouseY;
		isTileDragging = true;
	}
	//x vars
	int start_x = tileDragStartX;
	int end_x = currMouseX;
	if(end_x < start_x){
		int temp = end_x;
		end_x = start_x;
		start_x = temp;
	}
	//y vars
	int start_y = tileDragStartY;
	int end_y = currMouseY;
	if(end_y < start_y){
		int temp = end_y;
		end_y = start_y;
		start_y = temp;
	}
	//remove old drag previews
	while(dragPreviews.size() > 0){
		SpriteManager::GetInstance().RemoveSprite(dragPreviews[0]);
		dragPreviews.erase(dragPreviews.begin());
	}
	//display a preview of the drag area
	if(isTileDragging){
		for (int x=start_x;x <= end_x;x++) {
			for (int y=start_y;y <= end_y;y++) {
				//display the building hint on top of the tile pos
				Tile *tile = WorldManager::GetInstance().GetWorld()->GetTileAt(x,y);
				if(tile != nullptr){
					std::string filePath = "images/Cursor.png";
					Sprite sprite = SpriteManager::GetInstance().CreateSprite(filePath,(tile->GetX() * tile->GetWidth() * 24),(tile->GetY() * tile->GetHeight() * 24),24,24);
					dragPreviews.push_back(sprite);
				}
			}
		}
	}
	//end drag
	if(isTileDragging && event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT){
		for (int x=start_x;x <= end_x;x++) {
			for (int y=start_y;y <= end_y;y++) {
				WorldManager::GetInstance().GetWorld()->ChangeBuilding(buildingType,x,y);
			}
		}
		isTileDragging = false;
	}
}

void MouseManager::UpdateCameraMove(SDL_Event *event,Camera *camera){
	if(event->type == SDL_MOUSEBUTTONDOWN && (event->button.button == SDL_BUTTON_MIDDLE || event->button.button == SDL_BUTTON_RIGHT)){
		isCameraMoving = true;
	}
	if(isCameraMoving){
		int diffX = lastMouseX - currMouseX;
		int diffY = lastMouseY - currMouseY;
		camera->MoveCamera(diffX * 0.75,diffY * 0.75);
	}
	if(event->type == SDL_MOUSEBUTTONUP && (event->button.button == SDL_BUTTON_MIDDLE || event->button.button == SDL_BUTTON_RIGHT)){
		isCameraMoving = false;
	}
}

void MouseManager::UpdateCameraZoom(SDL_Event *event,Camera *camera){
	if(event->type == SDL_MOUSEWHEEL){
		camera->ZoomCamera(event->wheel.y);
	}
}
