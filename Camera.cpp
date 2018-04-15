#include "Camera.h"

Camera::Camera(int startX,int startY){
	x = startX;
	y = startY;
	zoom = 1;
}

Camera::~Camera(void){
}

void Camera::MoveCamera(int addX,int addY){
	x += addX;
	x = Clamp(x,0,(WindowManager::GetInstance().GetWorldWidthPixels() - WindowManager::GetInstance().GetWindowWidth()) / zoom);
	y += addY;
	y = Clamp(y,0,(WindowManager::GetInstance().GetWorldHeightPixels() - WindowManager::GetInstance().GetWindowHeight()) / zoom);
}

void Camera::ZoomCamera(float scroll){
	zoom -= 0.1f * scroll;
	zoom = Clamp(zoom,0.5f,1.7f);
	MoveCamera(0,0);
}

int Camera::GetX(void){
	return x;
}

int Camera::GetY(void){
	return y;
}

float Camera::GetZoom(void){
	return zoom;
}

float Camera::Clamp(float value,float min,float max){
	if(value < min){
		value = min;
	}
	if(value > max){
		value = max;
	}
	return value;
}
