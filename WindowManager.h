#pragma once

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include "SDL_Includes.h"
#include "SpriteManager.h"
#include "Window.h"
#include <vector>

class Window;

class WindowManager {
public:
	~WindowManager(void);

	void Start(void);
	bool Update(SDL_Event *event);

	static WindowManager &GetInstance(void);

	int CreateNewWindow(int width,int height,std::string type,SDL_Color color = { 0,0,0,255 });
	void CloseAllWindows(bool closeMain = false);

	void CloseWindow(int ID = 0);
	Window *&GetWindow(int id = 0);
	SDL_Window *&GetSDLWindow(int ID = 0);
	int GetWindowID(int ID = 0);
	SDL_Color GetWindowColor(int ID = 0);

	int GetWorldWidthTiles(void);
	int GetWorldHeightTiles(void);

	int GetWorldWidthPixels(void);
	int GetWorldHeightPixels(void);

	int GetTileWidthTiles(void);
	int GetTileHeightTiles(void);

	int GetTileWidthPixels(void);
	int GetTileHeightPixels(void);

	int GetWindowWidth(void);
	int GetWindowHeight(void);
private:
	WindowManager(void);

	std::vector<Window*> windows;

	const int worldWidth = 50;
	const int worldHeight = 50;

	const int tileWidth = 1;
	const int tileHeight = 1;

	const int windowWidth = 640;
	const int windowHeight = 480;
};

#endif
