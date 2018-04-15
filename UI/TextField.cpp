#include "TextField.h"

TextField::TextField(const char *setText,int setX,int setY,int setWidth,int setHeight,std::function<void(std::string)> setOnTextUpdate,int setFontSize,int setWindow){
	isTyping = false;
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	onTextUpdate = setOnTextUpdate;
	fontSize = setFontSize;
	std::string filePath = "images/UI/TextField.png";
	window = setWindow;
	text.assign(setText);
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(filePath,x,y,width,height,"ui",window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(setText,{ 43,123,160,255 },fontSize,x+width/2,y+height/2,window));
	onTextUpdate(text);
}

TextField::~TextField(){
}

bool TextField::HandleEvents(SDL_Event *event){
	int mouseX = 0,mouseY = 0;
	if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
		if(event->button.button == SDL_BUTTON_LEFT){
			mouseX = event->button.x;
			mouseY = event->button.y;
			if(mouseX >= x && mouseX <= x+width && mouseY >= y && mouseY <= y+height){
				isTyping = true;
			}
		}
	}
	if(isTyping && event->type == SDL_KEYDOWN ){
		//handle backspace
		if(event->key.keysym.sym == SDLK_BACKSPACE && text.size() > 0){
			//take off character
			text.pop_back();
		}
	}
	if(isTyping && event->type == SDL_TEXTINPUT && text.size() < 2){
		 if(isdigit(event->text.text[0])){
			 //append character
			 text.push_back(event->text.text[0]);
		 }
	}
	SpriteManager::GetInstance().RemoveSprite(sprites[1],"ui");
	sprites[1] = SpriteManager::GetInstance().CreateSprite(text.c_str(),{ 43,123,160,255 },fontSize,x+width/2,y+height/2,window);
	onTextUpdate(text);
	return isTyping;
}

bool TextField::Equals(TextField *otherTextField){
	if(x == otherTextField->GetX() && y == otherTextField->GetY() && width == otherTextField->GetWidth() && height == otherTextField->GetHeight()){
		return true;
	}
	return false;
}

void TextField::SetIsTyping(bool setIsTyping){
	isTyping = setIsTyping;
}

bool TextField::GetIsTyping(void){
	return isTyping;
}

int TextField::GetWidth(void){
	return width;
}

int TextField::GetHeight(void){
	return height;
}

int TextField::GetX(void){
	return x;
}

int TextField::GetY(void){
	return y;
}

void TextField::SetText(std::string setText){
	text = setText;
	SpriteManager::GetInstance().RemoveSprite(sprites[1],"ui");
	sprites[1] = SpriteManager::GetInstance().CreateSprite(text.c_str(),{ 43,123,160,255 },fontSize,x+width/2,y+height/2,window);
	onTextUpdate(text);
}

std::string TextField::GetText(void){
	return text;
}

Sprite TextField::GetSprite(void){
	return sprites[0];
}

Sprite TextField::GetTextSprite(void){
	return sprites[1];
}
