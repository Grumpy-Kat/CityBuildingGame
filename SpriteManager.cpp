#include "SpriteManager.h"

SpriteManager::SpriteManager(void){
}

SpriteManager::~SpriteManager(void){
}

void SpriteManager::Start(void){
	//create renderer
	renderers.push_back(SDL_CreateRenderer(WindowManager::GetInstance().GetSDLWindow(),-1,SDL_RENDERER_ACCELERATED));
}

void SpriteManager::Update(Camera *camera){
	for(unsigned int i = 0;i < renderers.size();i++){
		SDL_SetRenderDrawColor(renderers[i],WindowManager::GetInstance().GetWindowColor(i).r,WindowManager::GetInstance().GetWindowColor(i).g,WindowManager::GetInstance().GetWindowColor(i).b,WindowManager::GetInstance().GetWindowColor(i).a);
		SDL_RenderClear(renderers[i]);
	}
	if(!sprites.empty()){
		for(unsigned int i = 0;i < sprites.size();i++){
			if(sprites[i].GetTexture() != nullptr){
				if(camera == nullptr){
					sprites[i].Draw();
				} else{
					sprites[i].Draw(camera->GetX(),camera->GetY(),camera->GetZoom());
				}
			}
		}
	}
	if(!overlays.empty()){
		for(unsigned int i = 0;i < overlays.size();i++){
			if(overlays[i].GetTexture() != nullptr){
				if(camera == nullptr){
					overlays[i].Draw();
				} else{
					overlays[i].Draw(camera->GetX(),camera->GetY(),camera->GetZoom());
				}
			}
		}
	}
	if(!animations.empty()){
		std::cout << "SpriteManager::Update 0" << std::endl;
		for(unsigned int i = 0;i < animations.size();i++){
			std::cout << "SpriteManager::Update 1" << std::endl;
			animations[i].Update();
			std::cout << "SpriteManager::Update 2" << std::endl;
			if(animations[i].GetTexture() != nullptr){
				std::cout << "SpriteManager::Update 3" << std::endl;
				if(camera == nullptr){
					std::cout << "SpriteManager::Update 4" << std::endl;
					animations[i].Draw();
					std::cout << "SpriteManager::Update 5" << std::endl;
				} else{
					std::cout << "SpriteManager::Update 6 " << animations[i].GetX() << " | " << animations[i].GetY() << " | " << animations[i].GetWidth() << " | " << animations[i].GetHeight() << " | " << animations[i].GetFilePath() << std::endl;
					animations[i].Draw(camera->GetX(),camera->GetY(),camera->GetZoom());
					std::cout << "SpriteManager::Update 7" << std::endl;
				}
				std::cout << "SpriteManager::Update 8" << std::endl;
			}
			std::cout << "SpriteManager::Update 9" << std::endl;
		}
		std::cout << "SpriteManager::Update 10" << std::endl;
	}
	if(!ui.empty()){
		for(unsigned int i = 0;i < ui.size();i++){
			if(ui[i].GetTexture() != nullptr){
				if(camera == nullptr){
					ui[i].Draw();
				} else{
					ui[i].Draw(camera->GetX(),camera->GetY(),camera->GetZoom());
				}
			}
		}
	}
	for(unsigned int i = 0;i < renderers.size();i++){
		SDL_RenderPresent(renderers[i]);
	}
}

void SpriteManager::End(void){
	for(unsigned int i = 0;i < sprites.size();i++){
		if(sprites[i].GetTexture() != NULL){
			SDL_DestroyTexture(sprites[i].GetTexture());
		}
	}
	sprites.clear();
	for(unsigned int i = 0;i < overlays.size();i++){
		if(overlays[i].GetTexture() != NULL){
			SDL_DestroyTexture(overlays[i].GetTexture());
		}
	}
	overlays.clear();
	for(unsigned int i = 0;i < animations.size();i++){
		if(animations[i].GetTexture() != NULL){
			SDL_DestroyTexture(animations[i].GetTexture());
		}
	}
	animations.clear();
	for(unsigned int i = 0;i < ui.size();i++){
		if(ui[i].GetTexture() != NULL){
			SDL_DestroyTexture(ui[i].GetTexture());
		}
	}
	ui.clear();
	for(unsigned int i = 0;i < renderers.size();i++){
		SDL_DestroyRenderer(renderers[i]);
	}
	renderers.clear();
}

SpriteManager &SpriteManager::GetInstance(void){
	static SpriteManager *instance = nullptr;
	if(instance == nullptr){
		instance = new SpriteManager;
	}
	return *instance;
}

Sprite SpriteManager::CreateSprite(std::__cxx11::string &filePath,int x,int y,std::string vector,int window){
	Sprite sprite;
	if(vector == "ui"){
		sprite = Sprite(filePath,x,y,window,true);
		ui.push_back(sprite);
	} else if(vector == "overlays"){
		sprite = Sprite(filePath,x,y,window,false);
		overlays.push_back(sprite);
	} else if(vector == "animations"){
		AnimatedSprite animSprite = AnimatedSprite(filePath,x,y,32,32,window,false);
		animations.push_back(animSprite);
		sprite = animSprite;
	} else{
		sprite = Sprite(filePath,x,y,window,false);
		sprites.push_back(sprite);
	}
	return sprite;
}

Sprite SpriteManager::CreateSprite(std::__cxx11::string &filePath,int x,int y,int width,int height,std::string vector,int window){
	Sprite sprite;
	if(vector == "ui"){
		sprite = Sprite(filePath,x,y,width,height,window,true);
		ui.push_back(sprite);
	} else if(vector == "overlays"){
		sprite = Sprite(filePath,x,y,width,height,window,false);
		overlays.push_back(sprite);
	} else if(vector == "animations"){
		AnimatedSprite animSprite = AnimatedSprite(filePath,x,y,width,height,window,false);
		animations.push_back(animSprite);
		sprite = animSprite;
	} else{
		sprite = Sprite(filePath,x,y,width,height,window,false);
		sprites.push_back(sprite);
	}
	return sprite;
}

Sprite SpriteManager::CreateSprite(const char *text,SDL_Color color,int fontSize,int x,int y,int window){
	Sprite sprite = Sprite(text,color,fontSize,x,y,window);
	ui.push_back(sprite);
	return sprite;
}

void SpriteManager::RemoveSprite(Sprite sprite,std::string vector){
	if(vector == "sprites"){
		if(!sprites.empty()){
			for(unsigned int i=0;i < sprites.size();i++){
				if(sprite.Equals(&sprites[i],false)){
					sprites.erase(sprites.begin() + i);
				}
			}
		}
		return;
	}
	if(vector == "overlays"){
		if(!overlays.empty()){
			for(unsigned int i=0;i < overlays.size();i++){
				if(sprite.Equals(&overlays[i],false)){
					overlays.erase(overlays.begin() + i);
				}
			}
		}
		return;
	}
	if(vector == "animations"){
		if(!animations.empty()){
			for(unsigned int i=0;i < animations.size();i++){
				if(sprite.Equals(&animations[i],false)){
					animations.erase(animations.begin() + i);
				}
			}
		}
		return;
	}
	if(!ui.empty()){
		for(unsigned int i=0;i < ui.size();i++){
			if(sprite.Equals(&ui[i],true)){
				ui.erase(ui.begin() + i);
			}
		}
	}
}

Sprite SpriteManager::ChangeSpriteFilePath(std::string filePath,int x,int y,int width,int height,std::string vector,int window){
	int index = -1;
	Sprite sprite;
	if(vector == "ui"){
		sprite = Sprite(filePath,x,y,width,height,window,true);
	} else{
		sprite = Sprite(filePath,x,y,width,height,window,false);
	}
	if(vector == "sprites"){
		if(!sprites.empty()){
			for(unsigned int i=0;i < sprites.size();i++){
				if(sprite.Equals(&sprites[i],true)){
					index = i;
					break;
				}
			}
		}
	} else if(vector == "overlays"){
		if(!overlays.empty()){
			for(unsigned int i=0;i < overlays.size();i++){
				if(sprite.Equals(&overlays[i],true)){
					index = i;
					break;
				}
			}
		}
	} else if(vector == "animations"){
		if(!animations.empty()){
			for(unsigned int i=0;i < animations.size();i++){
				if(sprite.Equals(&animations[i],true)){
					index = i;
					break;
				}
			}
		}
	} else{
		if(!ui.empty()){
			for(unsigned int i=0;i < ui.size();i++){
				if(sprite.Equals(&ui[i],true)){
					index = i;
					break;
				}
			}
		}
	}
	if(index != -1) {
		if(vector == "sprites"){
			sprites[index].SetTexture(filePath,false);
			return sprites[index];
		}
		if(vector == "overlays"){
			overlays[index].SetTexture(filePath,false);
			return overlays[index];
		}
		if(vector == "animations"){
			animations[index].SetTexture(filePath,false);
			return animations[index];
		}
		ui[index].SetTexture(filePath,true);
		return ui[index];
	} else{
		return CreateSprite(filePath,sprite.GetX(),sprite.GetY(),sprite.GetWidth(),sprite.GetHeight(),vector,window);
	}
}

void SpriteManager::CreateNewRenderer(int window){
	renderers.push_back(SDL_CreateRenderer(WindowManager::GetInstance().GetSDLWindow(window),-1,SDL_RENDERER_ACCELERATED));
}

void SpriteManager::RemoveRenderer(int window){
	renderers.erase(renderers.begin() + window);
}

SDL_Renderer *&SpriteManager::GetRenderer(int window){
	return renderers[window];
}
