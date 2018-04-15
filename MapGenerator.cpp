#include "MapGenerator.h"

MapGenerator::MapGenerator(void){
}

MapGenerator::~MapGenerator(void){
}

void MapGenerator::Load(std::string filePath){
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	//Convert surface to display format
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface,SDL_GetWindowPixelFormat(WindowManager::GetInstance().GetSDLWindow()),NULL);
	//Create blank streamable texture
	SDL_Texture *map = SDL_CreateTexture(SpriteManager::GetInstance().GetRenderer(),SDL_GetWindowPixelFormat(WindowManager::GetInstance().GetSDLWindow()),SDL_TEXTUREACCESS_STREAMING,formattedSurface->w,formattedSurface->h);
	int pitch, width, height;
	void *pixels;
	SDL_LockTexture(map,NULL,&pixels,&pitch);
	//Copy loaded/formatted surface pixels
	memcpy(pixels,formattedSurface->pixels,formattedSurface->pitch * formattedSurface->h);
	SDL_SetTextureBlendMode(map, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(map,NULL,NULL,&width,&height);
	Uint32 *pixelData = (Uint32*) pixels;
	Uint32 grass = SDL_MapRGBA(SDL_GetWindowSurface(WindowManager::GetInstance().GetSDLWindow())->format,0x00,0xFF,0x00,0xFF);
	Uint32 dirt = SDL_MapRGBA(SDL_GetWindowSurface(WindowManager::GetInstance().GetSDLWindow())->format,0xFF,0x00,0x00,0xFF);
	int pixelCount = (pitch / 4) * height;
	//std::cout << pixelCount << " | " << pitch << " | " << height << std::endl;
	// manipulate pixels
	for(int x = 0;x < width;x++){
		for(int y = 0;y < height;y++){
			std::cout << x << " | " << y << " | " << pixelData[(x * width) + y] << " | " << grass << std::endl;
			if(pixelData[(x * width) + y] == grass){
				city[x][y] = 1;
				//std::cout << city[x][y] << std::endl;
				continue;
			}
			if(pixelData[(x * width) + y] == dirt){
				city[x][y] = 2;
				continue;
			}
			city[x][y] = 0;
		}
	}
	SDL_UnlockTexture(map);
}
