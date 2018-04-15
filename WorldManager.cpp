#include "WorldManager.h"

WorldManager::WorldManager(void){
}

WorldManager::~WorldManager(void){
	world = nullptr;
}

void WorldManager::Start(void){
	sprites.push_back(Sprite("Loading...",{ 43,123,160,255 },23,WindowManager::GetInstance().GetWindowWidth()/2,WindowManager::GetInstance().GetWindowHeight()/2,0));
	sprites[0].Draw();
	SDL_RenderPresent(SpriteManager::GetInstance().GetRenderer());
	world = new World(WindowManager::GetInstance().GetWorldWidthTiles(),WindowManager::GetInstance().GetWorldHeightTiles());
}

bool WorldManager::Update(int deltaTime){
	return world->Update(deltaTime);
}

void WorldManager::End(void){
	world = nullptr;
	sprites.clear();
}

WorldManager &WorldManager::GetInstance(void){
	static WorldManager *instance = nullptr;
	if(instance == nullptr){
		instance = new WorldManager;
	}
	return *instance;
}

World *&WorldManager::GetWorld(void){
	return world;
}
