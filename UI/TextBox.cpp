#include "TextBox.h"

TextBox::TextBox(const char *setButtonText,const char *setFileFolder,std::string setMode,int setX,int setY,std::function<void(std::string)> setOnEnter,std::function<bool(std::string)> setOnValidate,bool setShowFileName,int setWindow){
	x = setX;
	y = setY;
	width = 350;
	height = 300;
	onEnter = setOnEnter;
	onValidate = setOnValidate;
	mode = setMode;
	showFileName = setShowFileName;
	fileFolder.assign(setFileFolder);
	currActiveObj = 0;
	std::string arrowPreviousFilePath = "images/UI/ArrowPrevious.png";
	std::string arrowNextFilePath = "images/UI/ArrowNext.png";
	std::string buttonFilePath = "images/UI/ButtonDefault.png";
	window = setWindow;
	text.assign("");
	buttonText.assign(setButtonText);
	AddCurrActiveObj(0);
	if(mode != "Text"){
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(arrowPreviousFilePath,x + 65,y + 65,32,32,"ui",window));
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(arrowNextFilePath,x + 253,y + 65,32,32,"ui",window));
	}
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(buttonFilePath,x + 15,y + 140,150,50,"ui",window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(setButtonText,{ 43,123,160,255 },20,x + 90,y + 165,window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite(buttonFilePath,x + 185,y + 140,150,50,"ui",window));
	sprites.push_back(SpriteManager::GetInstance().CreateSprite("Cancel",{ 43,123,160,255 },20,x + 260,y + 165,window));
}

TextBox::~TextBox(void){
}

void TextBox::HandleEvents(SDL_Event *event){
	int mouseX = 0,mouseY = 0;
	//enter button events
	if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
		if(event->button.button == SDL_BUTTON_LEFT){
			mouseX = event->button.x;
			mouseY = event->button.y;
			if(mouseX >= x+15 && mouseX <= x+15+150 && mouseY >= y+140 && mouseY <= y+140+50){
				Enter(text);
			}
		}
	}
	//cancel button events
	if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
		if(event->button.button == SDL_BUTTON_LEFT){
			mouseX = event->button.x;
			mouseY = event->button.y;
			if(mouseX >= x+185 && mouseX <= x+185+150 && mouseY >= y+140 && mouseY <= y+140+50){
				WindowManager::GetInstance().CloseWindow(window);
			}
		}
	}
	if(mode != "Text"){
		//mouse previous button events
		if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
			if(event->button.button == SDL_BUTTON_LEFT){
				mouseX = event->button.x;
				mouseY = event->button.y;
				if(mouseX >= x+65 && mouseX <= x+65+32 && mouseY >= y+65 && mouseY <= y+65+32){
					AddCurrActiveObj(-1);
				}
			}
		}
		//mouse next button events
		if(event->type == SDL_MOUSEBUTTONDOWN && WindowManager::GetInstance().GetWindow(window)->GetIsMouseFocused()){
			if(event->button.button == SDL_BUTTON_LEFT){
				mouseX = event->button.x;
				mouseY = event->button.y;
				if(mouseX >= x+253 && mouseX <= x+253+32 && mouseY >= y+65 && mouseY <= y+65+32){
					AddCurrActiveObj(1);
				}
			}
		}
	} else{
		if(event->type == SDL_KEYDOWN ){
			//handle backspace
			if(event->key.keysym.sym == SDLK_BACKSPACE && editingText.size() > 0){
				//take off character
				editingText.pop_back();
			}
		}
		if(event->type == SDL_TEXTINPUT){
			 if(isdigit(event->text.text[0]) || isalpha(event->text.text[0]) || isspace(event->text.text[0])){
				 //append character
				 editingText.push_back(event->text.text[0]);
			 }
		}
		SpriteManager::GetInstance().RemoveSprite(sprites[1],"ui");
		sprites[1] = SpriteManager::GetInstance().CreateSprite(editingText.c_str(),{ 43,123,160,255 },20,x+175,y+65,window);
		text = fileFolder + editingText + ".txt";
	}
}

bool TextBox::Equals(TextBox *otherTextBox){
	if(x == otherTextBox->GetX() && y == otherTextBox->GetY() && width == otherTextBox->GetWidth() && height == otherTextBox->GetHeight()){
		return true;
	}
	return false;
}

int TextBox::GetWidth(void){
	return width;
}

int TextBox::GetHeight(void){
	return height;
}

int TextBox::GetX(void){
	return x;
}

int TextBox::GetY(void){
	return y;
}

Sprite TextBox::GetSprite(void){
	return sprites[0];
}

Sprite TextBox::GetTextSprite(void){
	return sprites[1];
}

void TextBox::Enter(std::string fileName){
	if(onValidate(fileName)){
		onEnter(fileName);
		WindowManager::GetInstance().CloseWindow(window);
	}
}

void TextBox::AddCurrActiveObj(int addCurrActiveObj){
	if(sprites.size() < 1 && showFileName){
		sprites.push_back(SpriteManager::GetInstance().CreateSprite("",{ 43,123,160,255 },20,x + 175,y + 15,window));
	}
	currActiveObj += addCurrActiveObj;
	struct dirent *entry;
	DIR *dir;
	char currPath[FILENAME_MAX];
	GetCurrentDir(currPath,sizeof(currPath));
	std::string filePath = std::string(currPath) + fileFolder;
	//open first to get amount of files in directory
	dir = opendir(filePath.c_str());
	if(dir == nullptr){
		perror("opendir: Path does not exist or could not be read.");
	}
	int numFiles = 0;
	while((entry = readdir(dir))){
		numFiles++;
	}
	closedir(dir);
	if(currActiveObj < 2){
		currActiveObj = 2;
	}
	if(currActiveObj > numFiles-1){
		currActiveObj = numFiles-1;
	}
	//work with files
	dir = opendir(filePath.c_str());
	if(dir == nullptr){
		perror("opendir: Path does not exist or could not be read.");
	}
	std::string name = "";
	if(mode == "Image"){
		int obj = 0;
		while((entry = readdir(dir))){
			//std::cout << "TextBox: " << entry->d_name << " | " << currActiveObj << " | " << numFiles << " | " << obj << std::endl;
			if(currActiveObj == obj){
				std::string imgPath = filePath + std::string(entry->d_name);
				name = std::string(entry->d_name).substr(0,std::string(entry->d_name).find("."));
				text = imgPath;
				//std::cout << "TextBox: displaying " << imgPath << std::endl;
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(imgPath,x + 125,y + 15,100,100,"ui",window));

			}
			obj++;
		}
	} else if(mode == "List"){
		int obj = 0;
		int placedObjs = 0;
		std::string imgFilePath = "images/UI/TextField.png";
		while((entry = readdir(dir))){
			if(currActiveObj == obj){
				std::string imgPath = filePath + std::string(entry->d_name);
				text = imgPath;
				std::cout << imgPath << std::endl;
				name = std::string(entry->d_name).substr(0,std::string(entry->d_name).find("."));

			}
			if(obj < 2){
				obj++;
				continue;
			}
			if(currActiveObj < 7){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(imgFilePath,x + 125,y + 30 +(placedObjs * 20),100,20,"ui",window));
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(std::string(entry->d_name).substr(0,std::string(entry->d_name).find(".")).c_str(),{ 43,123,160,255 },17,x + 175,y + 40 + (placedObjs * 20),window));
				placedObjs++;
				obj++;
				continue;
			}
			if(currActiveObj > numFiles-6){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(imgFilePath,x + 125,y + 30 +(placedObjs * 20),100,20,"ui",window));
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(std::string(entry->d_name).substr(0,std::string(entry->d_name).find(".")).c_str(),{ 43,123,160,255 },17,x + 175,y + 40 + (placedObjs * 20),window));
				placedObjs++;
				obj++;
				continue;
			}
			if(currActiveObj-2 > obj && currActiveObj+2 < obj){
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(imgFilePath,x + 125,y + 30 +(placedObjs * 20),100,20,"ui",window));
				sprites.push_back(SpriteManager::GetInstance().CreateSprite(std::string(entry->d_name).substr(0,std::string(entry->d_name).find(".")).c_str(),{ 43,123,160,255 },17,x + 175,y + 40 + (placedObjs * 20),window));
				placedObjs++;
				obj++;
				continue;
			}
		}
	} else if(mode == "Text"){
		std::string imgFilePath = "images/UI/TextField.png";
		editingText = name;
		text = fileFolder + editingText + ".txt";
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(imgFilePath,x + 125,y + 50,100,30,"ui",window));
		sprites.push_back(SpriteManager::GetInstance().CreateSprite(editingText.c_str(),{ 43,123,160,255 },20,x+175,y+65,window));
	}
	closedir(dir);
	if(showFileName){
		SpriteManager::GetInstance().RemoveSprite(sprites[0],"ui");
		sprites[0] = SpriteManager::GetInstance().CreateSprite(name.c_str(),{ 43,123,160,255 },20,x + 175,y + 15,window);
	}
}
