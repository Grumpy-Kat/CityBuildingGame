#include "WindowManager.h"

WindowManager::WindowManager(void){
}

WindowManager::~WindowManager(void){
}

void WindowManager::Start(void){
	//create window
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return;
	if(IMG_Init(IMG_INIT_PNG) < 0)
		return;
	if(TTF_Init() < 0)
		return;
	windows.push_back(new Window());
	windows[0]->Initialize(windowWidth,windowHeight,"Main",{ 0,0,0,255 },true);
}

bool WindowManager::Update(SDL_Event *event){
	for(unsigned int i = 1;i < windows.size();i++){
		if(windows[i]->HandleEvents(event)){
			windows.erase(windows.begin() + i);
			SpriteManager::GetInstance().RemoveRenderer(i);
		}
	}
	if(windows.size() == 0 || windows[0]->HandleEvents(event)){
		CloseAllWindows();
		return true;
	}
	return false;
}

WindowManager &WindowManager::GetInstance(void){
	static WindowManager* instance = nullptr;
	if(instance == nullptr){
		instance = new WindowManager;
	}
	return *instance;
}

int WindowManager::CreateNewWindow(int width,int height,std::string type,SDL_Color color){
	windows.push_back(new Window());
	windows[windows.size()-1]->Initialize(width,height,type,color,false);
	SpriteManager::GetInstance().CreateNewRenderer(windows.size()-1);
	return windows.size()-1;
}

void WindowManager::CloseAllWindows(bool closeMain){
	std::cout << "Closing All" << std::endl;
	for(unsigned int i = 1;i < windows.size();i++){
		windows[i]->CloseWindow();
		SpriteManager::GetInstance().RemoveRenderer(i);
	}
	if(closeMain){
		windows[0]->CloseWindow();
	}
	windows.clear();
}

void WindowManager::CloseWindow(int ID){
	windows[ID]->CloseWindow();
	SpriteManager::GetInstance().RemoveRenderer(ID);
	windows.erase(windows.begin() + ID);
}

Window *&WindowManager::GetWindow(int ID){
	return windows[ID];
}

SDL_Window *&WindowManager::GetSDLWindow(int ID){
	return windows[ID]->GetWindow();
}

int WindowManager::GetWindowID(int ID){
	return windows[ID]->GetWindowID();
}

SDL_Color WindowManager::GetWindowColor(int ID){
	return windows[ID]->GetColor();
}

int WindowManager::GetWorldWidthTiles(void){
	return worldWidth;
}

int WindowManager::GetWorldHeightTiles(void){
	return worldHeight;
}

int WindowManager::GetWorldWidthPixels(void){
	return worldWidth * tileWidth * 24;
}

int WindowManager::GetWorldHeightPixels(void){
	return worldHeight * tileHeight * 24;
}

int WindowManager::GetTileWidthTiles(void){
	return tileWidth;
}

int WindowManager::GetTileHeightTiles(void){
	return tileHeight;
}

int WindowManager::GetTileWidthPixels(void){
	return tileWidth * 24;
}

int WindowManager::GetTileHeightPixels(void){
	return tileHeight * 24;
}

int WindowManager::GetWindowWidth(void){
	return windowWidth;
}

int WindowManager::GetWindowHeight(void){
	return windowHeight;
}
