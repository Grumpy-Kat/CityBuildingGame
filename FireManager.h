#ifndef FIREMANAGER_H_
#define FIREMANAGER_H_

#include "WorldManager.h"
#include <stdlib.h>
#include <iostream>

class FireManager {
public:
	~FireManager();

	void Start(void);
	void Update(int deltaTime);
	void End(void);

	static FireManager &GetInstance(void);
private:
	FireManager();

	int timeSinceLastFire;
	int timeSinceLastTryFire;
	int timeSinceLastSpreadFire;
	bool fireAble;

	std::vector<std::vector<int>> coords;
};

#endif
