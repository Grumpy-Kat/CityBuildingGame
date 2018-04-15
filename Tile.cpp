#include "Tile.h"

Tile::Tile(void){
	isPlaceable = false;
	world = nullptr;
	x = 0;
	y = 0;
	width = WindowManager::GetInstance().GetTileWidthTiles();
	height = WindowManager::GetInstance().GetTileHeightTiles();
	std::string filePath = "images/Tile/WaterTile.png";
	if(sprites.size() == 0){
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x * width * 24,y * height * 24,24,24));
	} else{
		sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x * width * 24,y * height * 24,24,24);
	}
}

Tile::Tile(World *setWorld,int setX,int setY,int terrainType){
	isPlaceable = true;
	world = setWorld;
	x = setX;
	y = setY;
	width = WindowManager::GetInstance().GetTileWidthTiles();
	height = WindowManager::GetInstance().GetTileHeightTiles();
	std::string filePath = "";
	if(terrainType == 1){
		filePath = "images/Tile/GrassTile.png";
	} else if(terrainType == 2){
		filePath = "images/Tile/DirtTile.png";
	} else{
		filePath = "images/Tile/WaterTile.png";
		isPlaceable = false;
	}
	if(sprites.size() == 0){
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,(x * width * 24) ,(y * height * 24),24,24));
	} else{
		sprites[0] = SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,(x * width * 24) ,(y * height * 24),24,24);
	}
}

Tile::~Tile(void){
	world = nullptr;
}

bool Tile::IsNeighbor(Tile tile,bool diag = false){
	//horizontal or vertical neighbors
	if((std::abs(x - tile.x)) + (std::abs(y - tile.y)) == 1){
		return true;
	}
	//diagonal neighbors
	if((diag == true) && (std::abs(x - tile.x) == 1) && (std::abs(y - tile.y) == 1)){
		return true;
	}
	//not neighbors
	return false;
}

std::vector<Tile*> Tile::GetNeighbors(bool diag){
		//might return null
		std::vector<Tile*> ns;
		if(diag == false){
			//Tile Order : N E S W
			std::vector<Tile*> ns(4);
		} else {
			//Tile Order : N E S W NE SE SW NW
			std::vector<Tile*> ns(8);
		}
		Tile *n;
		//north
		n = world->GetTileAt(x,y+1);
		ns[0] = n;
		//east
		n = world->GetTileAt(x+1,y);
		ns[1] = n;
		//south
		n = world->GetTileAt(x,y-1);
		ns[2] = n;
		//west
		n = world->GetTileAt(x-1,y);
		ns[3] = n;
		if(diag == true){
			//northeast
			n = world->GetTileAt(x+1,y+1);
			ns[4] = n;
			//southeast
			n = world->GetTileAt(x+1,y-1);
			ns[5] = n;
			//southwest
			n = world->GetTileAt(x-1,y-1);
			ns[6] = n;
			//northwest
			n = world->GetTileAt(x-1,y+1);
			ns[7] = n;
		}
		return ns;
	}

World *Tile::GetWorld(void){
	return world;
}

int Tile::GetX(void){
	return x;
}

int Tile::GetY(void){
	return y;
}

int Tile::GetWidth(void){
	return width;
}

int Tile::GetHeight(void){
	return height;
}

Sprite Tile::GetSprite(void){
	return sprites[0];
}

bool Tile::IsPlaceable(void){
	return isPlaceable;
}
