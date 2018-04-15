#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include "../SDL_Includes.h"
#include "../SpriteManager.h"
#include "../Sprite.h"
#include <string>
#include <vector>
#include <functional>

class Sprite;

class Button {
public:
	Button(const char *setText,int setX,int setY,int setWidth,int setHeight,std::function<void(void)> setOnClick,int setFontSize,int setWindow);
	Button(std::string setImageFilePath,int relImgX,int relImgY,int imgWidth,int imgHeight,int setX,int setY,int setWidth,int setHeight,std::function<void(void)> setOnClick,int setWindow);
	~Button();

	void HandleEvents(SDL_Event *event);

	bool Equals(Button *otherButton);

	int GetWidth(void);
	int GetHeight(void);
	int GetX(void);
	int GetY(void);

	void ChangeText(std::string);
	std::string GetText(void);
	Sprite GetSprite(void);
	Sprite GetTextSprite(void);
private:
	std::function<void(void)> onClick;

	int window;

	int width;
	int height;
	int x;
	int y;

	std::string text;
	int fontSize;
	std::vector<Sprite> sprites;
};

#endif
