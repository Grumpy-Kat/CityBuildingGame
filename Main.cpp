#include "SDL_Includes.h"
#include "World.h"
#include "SpriteManager.h"
#include "MouseManager.h"
#include "UIManager.h"
#include "WindowManager.h"
#include "WorldManager.h"
#include "FireManager.h"

//g++ -std=c++0x -o Main.exe Main.cpp -lmingw32 -lstdc++fs -lSDL2main -lSDL2 -lSDL_image -lSDL_ttf

//---List of Future Addition---
//TODO: Fix issues with power and fire maps (does not calculate correctly when deleting power sources and fire sources because does consider other nearby sources)
//TODO: Give fire station use (stops fire 7/10 in coverage zone)
//TODO: Fires (ex: affected by fire station coverage and fire budget)
//TODO: Crime (ex: affected by police station coverage and police budget)
//TODO: Birth rate and death rate (update population on monthly basis affected by the rates; ex: affected by fire and crime)
//TODO: Land value (ex: affected by pollution or traffic or crime rates or fire protection, affects population and tax income)
//TODO: Multiple saves (ex: allow user to choose name)
//TODO: More buildings (can affect land value; ex: schools, college, stadium, airport, casino, police station)
//TODO: Educated and uneducated jobs (work with school system; ex: educated == commercial and uneducated == industrial, affects demand based on number of schools)
//TODO: Pollution (ex: caused by industrial or powerplants, reduces tax payment)
//TODO: Audio (using SDL_mixer; ex: when placing buildings or getting taxes or taking out loan)
//TODO: MAYBE Multi-tile buildings (buildings that aren't 1 * 1)

void MainFunc(bool isLoading = false,std::string path = "");

int main(int argc,char *argv[]){
	//set up game loop
	bool isRunning = true;
	int frameStart = 0,frameEnd = 0,deltaTime = 0;
	SDL_Event event;
	//start managers
	WindowManager::GetInstance().Start();
	UIManager::GetInstance().Start();
	SpriteManager::GetInstance().Start();
	MenuManager::GetInstance().Start();
	//set settings
	MenuManager::GetInstance().CreateStartMenu();
	bool isCreating = false,isLoading = false,isQuitting = false;
	std::string filePath = "";
	//start game loop
	while(isRunning){
		if (deltaTime < 1){
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		//check for events
		while(SDL_PollEvent(&event) != 0){
			//check if quit button was clicked
			if(WindowManager::GetInstance().Update(&event)){
				isQuitting = true;
				isRunning = false;
			}
			UIManager::GetInstance().Update(&event);
		}
		SpriteManager::GetInstance().Update(nullptr);
		if(MenuManager::GetInstance().GetStartMenu()->GetIsCreating() && !isCreating && !isLoading){
			isCreating = true;
			MenuManager::GetInstance().CreateNewMenu();
		}
		if(MenuManager::GetInstance().GetStartMenu()->GetIsLoading() && !isCreating && !isLoading){
			isLoading = true;
			MenuManager::GetInstance().CreateLoadMenu();
		}
		if(isLoading && MenuManager::GetInstance().GetStartMenu()->GetLoadPath() != ""){
			filePath = MenuManager::GetInstance().GetStartMenu()->GetLoadPath();
			isRunning = false;
		}
		if(isCreating && MenuManager::GetInstance().GetStartMenu()->GetCreatingPath() != ""){
			filePath = MenuManager::GetInstance().GetStartMenu()->GetCreatingPath();
			isRunning = false;
		}
		if(MenuManager::GetInstance().GetStartMenu()->GetIsQuitting()){
			isQuitting = true;
			isRunning = false;
		}
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}
	WindowManager::GetInstance().CloseAllWindows(true);
	UIManager::GetInstance().End();
	SpriteManager::GetInstance().End();
	MenuManager::GetInstance().End();
	if(!isQuitting){
		MainFunc(isLoading,filePath);
	}
	return 0;
}

void MainFunc(bool isLoading,std::string filePath){
	std::cout << isLoading << " | " << filePath << std::endl;
	//set up game loop
	bool isRunning = true;
	int frameStart = 0,frameEnd = 0,deltaTime = 0;
	SDL_Event event;
	//start managers
	MouseManager::GetInstance().Start();
	WindowManager::GetInstance().Start();
	UIManager::GetInstance().Start();
	SpriteManager::GetInstance().Start();
	WorldManager::GetInstance().Start();
	MoneyManager::GetInstance().Start();
	PopulationManager::GetInstance().Start();
	FireManager::GetInstance().Start();
	//create camera
	Camera camera((WindowManager::GetInstance().GetWorldWidthPixels() - WindowManager::GetInstance().GetWindowWidth()) / 2,(WindowManager::GetInstance().GetWorldHeightPixels() - WindowManager::GetInstance().GetWindowHeight()) / 2);
	if(!isLoading){
		//set settings
		MenuManager::GetInstance().CreateMainMenu();
		MoneyManager::GetInstance().AddAmount(20000);
		PopulationManager::GetInstance().AddRedPop(0);
		PopulationManager::GetInstance().AddComPop(0);
		PopulationManager::GetInstance().AddIndPop(0);
		//create world
		WorldManager::GetInstance().GetWorld()->SetUpWorld(filePath);
	} else{
		//set settings
		MenuManager::GetInstance().CreateMainMenu();
		//create world
		WorldManager::GetInstance().GetWorld()->Load(filePath);
	}
	//start game loop
	while(isRunning){
		if (deltaTime < 1){
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		//check for events
		while(SDL_PollEvent(&event) != 0){
			//check if quit button was clicked
			MouseManager::GetInstance().Update(&event,&camera);
			if(WindowManager::GetInstance().Update(&event)){
				isRunning = false;
			}
			UIManager::GetInstance().Update(&event);
		}
		SpriteManager::GetInstance().Update(&camera);
		if(WorldManager::GetInstance().Update(deltaTime)){
			isRunning = false;
		}
		FireManager::GetInstance().Update(deltaTime);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}
	if(WorldManager::GetInstance().GetWorld()->loadingNew == true){
		WorldManager::GetInstance().GetWorld()->loadingNew = false;
		WindowManager::GetInstance().CloseAllWindows(true);
		UIManager::GetInstance().End();
		SpriteManager::GetInstance().End();
		WorldManager::GetInstance().End();
		MenuManager::GetInstance().End();
		MainFunc(true);
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
