#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include "World.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <vector>

class World;

class WorldManager {
public:
	WorldManager();
	~WorldManager();

	void Start(void);
	 bool Update(int deltaTime);
	 void End(void);

	static WorldManager &GetInstance(void);

	World *&GetWorld(void);
private:
	World *world;
	std::vector<Sprite> sprites;
};

#endif
