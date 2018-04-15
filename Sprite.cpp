#include "Sprite.h"

Sprite::Sprite(void){
	renderer = nullptr;
	texture = nullptr;
	filePath = "";
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	window = -1;
	type = SpriteType::Other;
	color = { 0,0,0,0 };
}

Sprite::Sprite(std::__cxx11::string &setFilePath,int setX,int setY,int setWindow,bool ui){
	x = setX;
	y = setY;
	width = 0;
	height = 0;
	window = setWindow;
	renderer = SpriteManager::GetInstance().GetRenderer(window);
	SetTexture(setFilePath,ui);
}

Sprite::Sprite(std::__cxx11::string &setFilePath,int setX,int setY,int setWidth,int setHeight,int setWindow,bool ui){
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	window = setWindow;
	renderer = SpriteManager::GetInstance().GetRenderer(window);
	SetTexture(setFilePath,ui);
}

Sprite::Sprite(const char *setText,SDL_Color setColor,int fontSize,int setX,int setY,int setWindow){
	x = setX;
	y = setY;
	type = SpriteType::Text;
	window = setWindow;
	renderer = SpriteManager::GetInstance().GetRenderer(window);
	color = setColor;
	filePath = std::string(setText);
	TTF_Font *font = TTF_OpenFont("fonts/ARIAL.TTF",fontSize);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font,setText,setColor);
	texture = SDL_CreateTextureFromSurface(renderer,textSurface);
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
}

Sprite::~Sprite(void){	}

void Sprite::Update(void){	}

void Sprite::Draw(int cameraX,int cameraY,float zoom){
	if(texture != NULL && renderer != NULL){
		SDL_Rect dest;
		 if(type == SpriteType::UI){
			//draw UI normally, with no effect from camera placement
			dest.x = x;
			dest.y = y;
			dest.w = width;
			dest.h = height;
		} else if(color.a == 0){
			//draw objects normally, with effect from camera placement
			dest.x = (x - cameraX) / zoom;
			dest.y = (y - cameraY) / zoom;
			dest.w = (width / zoom) + 1;
			dest.h = (height / zoom) + 1;
			if(type == SpriteType::AnimatedSprite){
				std::cout << "Drawing" << std::endl;
			}
		} else{
			//draw text with a middle align, with no effect from camera placement
			dest.x = x - (width / 2);
			dest.y = y - (height / 2);
			dest.w = width;
			dest.h = height;
		}
		SDL_RenderCopy(renderer,texture,nullptr,&dest);
	} else{
		std::cout << "Draw: Texture or renderer is null" << std::endl;
	}
}

bool Sprite::Equals(Sprite *otherSprite,bool filePathChanged){
	if(x == otherSprite->GetX() && y == otherSprite->GetY() && width == otherSprite->GetWidth() && height == otherSprite->GetHeight() && type == otherSprite->GetType() && window == otherSprite->GetWindow()){
		if(!filePathChanged  && filePath == otherSprite->GetFilePath()){
			return true;
		} else if(filePathChanged){
			return true;
		}
	}
	return false;
}

SDL_Texture *Sprite::GetTexture(void){
	return texture;
}

void Sprite::SetTexture(std::string setFilePath,bool ui){
	filePath = setFilePath;
	texture = IMG_LoadTexture(renderer,filePath.c_str());
	if(texture == NULL){
		std::cout << "SetTexture: Image '" << filePath << "' not found." << std::endl;
	} else{
		if(width == 0 || height == 0){
			SDL_QueryTexture(texture,NULL,NULL,&width,&height);
		}
		if(ui || filePath.find("UI") != std::string::npos){
			type = SpriteType::UI;
		} else if(filePath.find("Tile") != std::string::npos){
			type = SpriteType::Tile;
		} else if(filePath.find("Cursor") != std::string::npos){
			type = SpriteType::Cursor;
		} else if(filePath.find("Residential") != std::string::npos){
			type = SpriteType::Residential;
		} else if(filePath.find("Commercial") != std::string::npos){
			type = SpriteType::Commercial;
		} else if(filePath.find("Industrial") != std::string::npos){
			type = SpriteType::Industrial;
		} else if(filePath.find("Road") != std::string::npos){
			type = SpriteType::Road;
		} else if(filePath.find("Powerline") != std::string::npos){
			type = SpriteType::Powerline;
		} else if(filePath.find("CoalPowerplant") != std::string::npos){
			type = SpriteType::CoalPowerplant;
		} else{
			type = SpriteType::Other;
		}
		color = { 0,0,0,0 };
	}
}

std::string Sprite::GetFilePath(void){
	return filePath;
}

int Sprite::GetWindow(void){
	return window;
}

int Sprite::GetWidth(void){
	return width;
}

int Sprite::GetHeight(void){
	return height;
}

int Sprite::GetX(void){
	return x;
}

int Sprite::GetY(void){
	return y;
}

Sprite::SpriteType Sprite::GetType(void){
	return type;
}

SDL_Color Sprite::GetColor(void){
	return color;
}
