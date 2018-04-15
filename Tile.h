#ifndef TILE_H_
#define TILE_H_

#include "SDL_Includes.h"
#include "World.h"
#include "Sprite.h"
#include <cmath>
#include <vector>
#include <string>

class World;
class Sprite;

class Tile {
public:
	Tile(void);
	Tile(World *setWorld,int setX,int setY,int terrainType);
	~Tile(void);

	bool IsNeighbor(Tile tile,bool diag);
	std::vector<Tile*> GetNeighbors(bool diag);

	World *GetWorld(void);
	int GetX(void);
	int GetY(void);
	int GetWidth(void);
	int GetHeight(void);

	Sprite GetSprite(void);

	bool IsPlaceable(void);
private:
	World *world;
	int x;
	int y;
	int width;
	int height;

	std::vector<Sprite> sprites;

	bool isPlaceable;
};

#endif
