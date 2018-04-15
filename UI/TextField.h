#ifndef UI_TEXTFIELD_H_
#define UI_TEXTFIELD_H_

#include "../SDL_Includes.h"
#include "../SpriteManager.h"
#include "../Sprite.h"
#include <string>
#include <vector>
#include <functional>

class Sprite;

class TextField {
public:
	TextField(const char *setText,int setX,int setY,int setWidth,int setHeight,std::function<void(std::string)> setOnTextUpdate,int setFontSize,int setWindow);
	~TextField(void);

	bool HandleEvents(SDL_Event *event);

	bool Equals(TextField *otherTextField);

	void SetIsTyping(bool setIsTyping);
	bool GetIsTyping(void);

	int GetWidth(void);
	int GetHeight(void);
	int GetX(void);
	int GetY(void);

	void SetText(std::string setText);
	std::string GetText(void);

	Sprite GetSprite(void);
	Sprite GetTextSprite(void);
private:
	int window;

	std::function<void(std::string)> onTextUpdate;
	bool isTyping;

	int width;
	int height;
	int x;
	int y;

	std::string text;
	int fontSize;
	std::vector<Sprite> sprites;
};

#endif
