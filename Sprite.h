#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL_Includes.h"
#include "SpriteManager.h"
#include <iostream>
#include <string>
#include <vector>

class SpriteManager;

class Sprite {
public:
	enum SpriteType{
		Tile,
		Cursor,
		UI,
		Text,
		Residential,
		Commercial,
		Industrial,
		Road,
		Powerline,
		CoalPowerplant,
		AnimatedSprite,
		Other
	};

	Sprite(void);
	Sprite(std::__cxx11::string &filePath,int setX,int setY,int window,bool ui);
	Sprite(std::__cxx11::string &filePath,int setX,int setY,int setWidth,int setHeight,int window,bool ui);
	Sprite(const char *setText,SDL_Color setColor,int fontSize,int setX,int setY,int window);
	virtual ~Sprite(void);

	virtual void Update();
	void Draw(int cameraX = 0,int cameraY = 0,float zoom = 1);

	bool Equals(Sprite *otherSprite,bool filePathChanged);

	SpriteType GetType(void);

	SDL_Texture *GetTexture(void);
	void SetTexture(std::string setFilePath,bool ui);
	std::string GetFilePath(void);
	int GetWindow(void);

	int GetWidth(void);
	int GetHeight(void);
	int GetX(void);
	int GetY(void);

	SDL_Color GetColor(void);
protected:
	SpriteType type;

	SDL_Renderer *renderer;

	SDL_Texture *texture;
	std::string filePath;
	int window;

	int width;
	int height;
	int x;
	int y;

	SDL_Color color;
};

class AnimatedSprite : public Sprite {
public:
	enum AnimatedSpriteType{
		Fire,
		Other
	};

	AnimatedSprite(void);
	AnimatedSprite(std::__cxx11::string &filePath,int setX,int setY,int window,bool ui);
	AnimatedSprite(std::__cxx11::string &filePath,int setX,int setY,int setWidth,int setHeight,int window,bool ui);
	~AnimatedSprite(void);

	void Update(void);

	AnimatedSpriteType GetAnimationType(void);

	std::vector<SDL_Texture*> GetTextures(void);
	void SetTexture(std::string setFilePath,bool ui);

	int GetTotalFrames(void);
	int GetCurrFrame(void);
private:
	AnimatedSpriteType animationType;

	std::vector<SDL_Texture*> textures;

	unsigned int totalFrames;
	unsigned int currFrame;
};

#endif
