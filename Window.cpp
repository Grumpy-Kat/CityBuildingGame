#include "Window.h"

Window::Window(void){
	window = nullptr;
	width = 0;
	height = 0;
	color = { 0,0,0,1  };
	isMouseFocused = false;
	isKeyboardFocused = false;
	isMain = false;
	windowID = -1;
	type = "";
}

Window::~Window(void){
}

bool Window::Initialize(int setWidth,int setHeight,std::string setType,SDL_Color setColor,bool setIsMain){
	window = SDL_CreateWindow("City Building Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,setWidth,setHeight,SDL_WINDOW_SHOWN);
	if(window != nullptr){
		width = setWidth;
		height = setHeight;
		color = setColor;
		isMouseFocused = true;
		isKeyboardFocused = true;
		isMain = setIsMain;
		windowID = SDL_GetWindowID(window);
		type = setType;
	} else{
		std::cout << "Window could not be created!" << std::endl;
	}
	return window != nullptr;
}

bool Window::HandleEvents(SDL_Event *event){
	bool closed = false;
	if(event->type == SDL_WINDOWEVENT && event->window.windowID == windowID){
		switch(event->window.event){
			case SDL_WINDOWEVENT_ENTER: {
				isMouseFocused = true;
				break;
			}
			case SDL_WINDOWEVENT_LEAVE: {
				isMouseFocused = false;
				break;
			}
			case SDL_WINDOWEVENT_FOCUS_GAINED: {
				isKeyboardFocused = true;
				break;
			}
			case SDL_WINDOWEVENT_FOCUS_LOST: {
				isKeyboardFocused = false;
				break;
			}
			case SDL_WINDOWEVENT_CLOSE: {
				CloseWindow();
				closed = true;
				break;
			}
		}
	}
	return closed;
}

void Window::CloseWindow(void){
	if(window != nullptr){
		SDL_DestroyWindow(window);
	}
	window = nullptr;
	width = 0;
	height = 0;
	color = { 0,0,0,1  };
	isMouseFocused = false;
	isKeyboardFocused = false;
	if(type == "Main"){
		MenuManager::GetInstance().CloseMainMenu();
	}
	if(type == "Start"){
		MenuManager::GetInstance().CloseStartMenu();
	}
	if(type == "New"){
		MenuManager::GetInstance().CloseNewMenu();
	}
	if(type == "Load"){
		MenuManager::GetInstance().CloseLoadMenu();
	}
	if(type == "Save"){
		MenuManager::GetInstance().CloseSaveMenu();
	}
	if(type == "Loan"){
		MenuManager::GetInstance().CloseLoanMenu();
	}
	if(type == "Tax"){
		MenuManager::GetInstance().CloseTaxMenu();
	}
}

SDL_Window *&Window::GetWindow(void){
	return window;
}

int Window::GetWidth(void){
	return width;
}

int Window::GetHeight(void){
	return height;
}

SDL_Color Window::GetColor(void){
	return color;
}

bool Window::GetIsMouseFocused(){
	return isMouseFocused;
}

bool Window::GetIsKeyboardFocused(){
	return isKeyboardFocused;
}

bool Window::GetIsMain(void){
	return isMain;
}

int Window::GetWindowID(void){
	return windowID;
}

std::string Window::GetType(void){
	return type;
}
