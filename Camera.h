#ifndef CAMERA_H_
#define CAMERA_H_

#include "WindowManager.h"
#include <iostream>
#include <algorithm>

class Camera {
public:
	Camera(int startX = 0,int startY = 0);
	~Camera(void);

	void MoveCamera(int addX,int addY);

	void ZoomCamera(float scroll);

	int GetX(void);
	int GetY(void);

	float GetZoom(void);
private:
	float Clamp(float value,float min,float max);

	int x;
	int y;

	float zoom;
};

#endif
