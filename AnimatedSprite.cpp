#include "Sprite.h"

AnimatedSprite::AnimatedSprite(void){
	renderer = nullptr;
	texture = nullptr;
	filePath = "";
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	window = -1;
	type = SpriteType::AnimatedSprite;
	color = { 0,0,0,0 };
	animationType = AnimatedSpriteType::Other;
	totalFrames = 0;
	currFrame = 0;
}

AnimatedSprite::AnimatedSprite(std::__cxx11::string &setFilePath,int setX,int setY,int setWidth,int setHeight,int setWindow,bool ui){
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	window = setWindow;
	renderer = SpriteManager::GetInstance().GetRenderer(window);
	type = SpriteType::AnimatedSprite;
	SetTexture(setFilePath,ui);
}

AnimatedSprite::~AnimatedSprite(void){
}

void AnimatedSprite::Update(){
	std::cout << "AnimatedSprite::Update 0" << std::endl;
	currFrame++;
	std::cout << "AnimatedSprite::Update 1" << std::endl;
	if(currFrame >= totalFrames){
		std::cout << "AnimatedSprite::Update 2" << std::endl;
		currFrame = 0;
		std::cout << "AnimatedSprite::Update 3" << std::endl;
	}
	std::cout << "AnimatedSprite::Update 4 " << currFrame << " | " << totalFrames << std::endl;
	texture = textures[currFrame];
	std::cout << "AnimatedSprite::Update 5" << std::endl;
}

std::vector<SDL_Texture*> AnimatedSprite::GetTextures(void){
	return textures;
}

void AnimatedSprite::SetTexture(std::string setFilePath,bool ui){
	filePath = setFilePath;
	texture = IMG_LoadTexture(renderer,filePath.c_str());
	if(texture == NULL){
		std::cout << "SetTexture: Image '" << filePath << "' not found." << std::endl;
	} else{
		if(filePath.find("Fire") != std::string::npos){
			animationType = AnimatedSpriteType::Fire;
		} else{
			animationType = AnimatedSpriteType::Other;
		}
		int totalWidth = 0, totalHeight = 0;
		SDL_QueryTexture(texture,NULL,NULL,&totalWidth,&totalHeight);
		for(unsigned int j=0;j < totalHeight/32;j++){
			for(unsigned int i=0;i < totalWidth/32;i++){
				textures.push_back(SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,32,32));
				SDL_SetTextureBlendMode(textures[i+j],SDL_BLENDMODE_BLEND);
				SDL_Rect rect = {i*32,j*32,32,32};
				SDL_SetRenderTarget(renderer,textures[textures.size()-1]);
				SDL_RenderCopy(renderer,texture,&rect,NULL);
			}
		}
		SDL_SetRenderTarget(renderer,nullptr);
		totalFrames = textures.size();
		texture = textures[0];
		color = { 0,0,0,0 };
	}
}


AnimatedSprite::AnimatedSpriteType AnimatedSprite::GetAnimationType(void){
	return animationType;
}
