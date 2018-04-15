#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "Sprite.h"
#include "Camera.h"
#include <vector>
#include <string>
#include <algorithm>

class Sprite;
class AnimatedSprite;
class Camera;

class SpriteManager {
public:
	~SpriteManager(void);

	void Start(void);
	void Update(Camera *camera);
	void End(void);

	static SpriteManager &GetInstance(void);

	Sprite CreateSprite(std::__cxx11::string &filePath,int x,int y,std::string vector = "sprites",int window = 0);
	Sprite CreateSprite(std::__cxx11::string &filePath,int x,int y,int width,int height,std::string vector = "sprites",int window = 0);
	Sprite CreateSprite(const char *text,SDL_Color color,int fontSize,int x,int y,int window = 0);
	void RemoveSprite(Sprite sprite,std::string vector = "sprites");
	Sprite ChangeSpriteFilePath(std::string filePath,int x,int y,int width = 0,int height = 0,std::string vector = "sprites",int window = 0);

	void CreateNewRenderer(int window);
	void RemoveRenderer(int window);
	SDL_Renderer *&GetRenderer(int window = 0);
private:
	SpriteManager();

	std::vector<SDL_Renderer*> renderers;

	std::vector<Sprite> sprites;
	std::vector<Sprite> overlays;
	std::vector<AnimatedSprite> animations;
	std::vector<Sprite> ui;
};

#endif
