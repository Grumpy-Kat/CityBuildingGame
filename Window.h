#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL_Includes.h"
#include "MenuManager.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

class Window {
public:
	Window(void);
	~Window(void);

	bool Initialize(int setWidth,int setHeight,std::string setType,SDL_Color setColor = { 0,0,0,255 },bool setIsMain = false);

	bool HandleEvents(SDL_Event *event);

	void CloseWindow(void);

	SDL_Window *&GetWindow(void);

	int GetWidth(void);
	int GetHeight(void);

	SDL_Color GetColor(void);

	bool GetIsMouseFocused(void);
	bool GetIsKeyboardFocused(void);

	bool GetIsMain(void);
	int GetWindowID(void);
	std::string GetType(void);
private:
	SDL_Window *window;

	int width;
	int height;

	SDL_Color color;

	bool isMouseFocused;
	bool isKeyboardFocused;

	bool isMain;
	unsigned int windowID;
	std::string type;
};

#endif
