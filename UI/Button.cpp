#include "Button.h"

Button::Button(const char *setText,int setX,int setY,int setWidth,int setHeight,std::function<void(void)> setOnClick,int setFontSize,int setWindow){
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	onClick = setOnClick;
	fontSize = setFontSize;
	std::string filePath = "images/UI/ButtonDefault.png";
	window = setWindow;
	text.assign(setText);
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x,y,width,height,"ui",window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(setText,{ 43,123,160,255 },fontSize,x+width/2,y+height/2,window));
}

Button::Button(std::string setImageFilePath,int relImgX,int relImgY,int imgWidth,int imgHeight,int setX,int setY,int setWidth,int setHeight,std::function<void(void)> setOnClick,int setWindow){
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	onClick = setOnClick;
	fontSize = 0;
	std::string filePath = "images/UI/ButtonDefault.png";
	window = setWindow;
	text = setImageFilePath;
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x,y,width,height,"ui",window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(text,x + relImgX,y + relImgY,imgWidth,imgHeight,"ui",window));
	//std::cout << sprites[1].GetFilePath() << " | " << (x + relImgX) << " | " << (y + relImgY) << std::endl;
}

Button::~Button(){
}

void Button::HandleEvents(SDL_Event *event){
	int mouseX = 0,mouseY = 0;
	if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
		if(event->button.button == SDL_BUTTON_LEFT){
			mouseX = event->button.x;
			mouseY = event->button.y;
			if(mouseX >= x && mouseX <= x+width && mouseY >= y && mouseY <= y+height){
				std::string filePath = "images/UI/ButtonClick.png";
				SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x,y,width,height,"ui",window);
				onClick();
			}
		}
	}
	if(event->type == SDL_MOUSEBUTTONUP){
		if(event->button.button == SDL_BUTTON_LEFT){
			mouseX = event->button.x;
			mouseY = event->button.y;
			if(mouseX >= x && mouseX <= x+width && mouseY >= y && mouseY <= y+height){
				std::string filePath = "images/UI/ButtonDefault.png";
				SpriteManager::GetInstance().ChangeSpriteFilePath(filePath,x,y,width,height,"ui",window);
			}
		}
	}
}

bool Button::Equals(Button *otherButton){
	if(x == otherButton->GetX() && y == otherButton->GetY() && width == otherButton->GetWidth() && height == otherButton->GetHeight()){
		return true;
	}
	return false;
}

int Button::GetWidth(void){
	return width;
}

int Button::GetHeight(void){
	return height;
}

int Button::GetX(void){
	return x;
}

int Button::GetY(void){
	return y;
}

void Button::ChangeText(std::string setText){
	SpriteManager::GetInstance().RemoveSprite(sprites[1],"ui");
	text = setText;
	sprites[1] = SpriteManager::GetInstance().CreateSprite(text.c_str(),{ 43,123,160,255 },fontSize,x+width/2,y+height/2,window);
}

std::string Button::GetText(void){
	return text;
}

Sprite Button::GetSprite(void){
	return sprites[0];
}

Sprite Button::GetTextSprite(void){
	return sprites[1];
}
