#ifndef UI_TEXTBOX_H_
#define UI_TEXTBOX_H_

#include "../SDL_Includes.h"
#include "../SpriteManager.h"
#include "../Sprite.h"
#include "../WindowManager.h"
#include "../UIManager.h"
#include "Button.h"
#include <string>
#include <vector>
#include <functional>
#include <dirent.h>
#include <direct.h>
#include <stdio.h>
#include <iostream>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

class Button;
class Sprite;

class TextBox {
public:
	//TextBox(const char *setButtonText,const char *setText,int setX,int setY,std::function<void(std::string)> setOnEnter,std::function<bool(std::string)> setOnValidate,int setWindow);
	TextBox(const char *setButtonText,const char *setFileFolder,std::string setMode,int setX,int setY,std::function<void(std::string)> setOnEnter,std::function<bool(std::string)> setOnValidate,bool setShowFileName,int setWindow);
	~TextBox(void);

	void HandleEvents(SDL_Event *event);

	bool Equals(TextBox *otherTextBox);

	int GetWidth(void);
	int GetHeight(void);
	int GetX(void);
	int GetY(void);

	Sprite GetSprite(void);
	Sprite GetTextSprite(void);
private:
	void Enter(std::string fileName);

	void AddCurrActiveObj(int addCurrActiveObj);

	/*int window;

	std::function<void(std::string)> onEnter;
	std::function<bool(std::string)> onValidate;
	bool isTyping;

	int width;
	int height;
	int x;
	int y;

	std::string text;
	std::vector<Sprite> sprites;
	std::string buttonText;*/
	int window;

	std::function<void(std::string)> onEnter;
	std::function<bool(std::string)> onValidate;

	int width;
	int height;
	int x;
	int y;

	std::string mode;
	bool showFileName;
	std::string fileFolder;

	int currActiveObj;
	std::string editingText;

	std::string text;
	std::vector<Sprite> sprites;
	std::string buttonText;
};

#endif
