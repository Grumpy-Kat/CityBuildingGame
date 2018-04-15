#include "UIManager.h"

UIManager::UIManager(){
}

UIManager::~UIManager(){
}

void UIManager::Start(void){
	prevTypingTextField = -1;
}

void UIManager::Update(SDL_Event *event){
	if(!buttons.empty()){
		for(unsigned int i = 0;i < buttons.size();i++){
			buttons[i].HandleEvents(event);
		}
	}
	if(!textFields.empty()){
		for(unsigned int i = 0;i < textFields.size();i++){
			if(textFields[i].HandleEvents(event)){
				if(prevTypingTextField == -1){
					prevTypingTextField = i;
				}
				if(i != prevTypingTextField){
					textFields[prevTypingTextField].SetIsTyping(false);
					prevTypingTextField = i;
				}
			}
		}
	}
	if(!textBoxes.empty()){
		for(unsigned int i = 0;i < textBoxes.size();i++){
			textBoxes[i].HandleEvents(event);
		}
	}
}

void UIManager::End(void){
	buttons.clear();
	textFields.clear();
	textBoxes.clear();
}

UIManager &UIManager::GetInstance(){
	static UIManager *instance = nullptr;
	if(instance == nullptr){
		instance = new UIManager;
	}
	return *instance;
}

Button UIManager::CreateButton(const char *text,int x,int y,int width,int height,std::function<void(void)> onClick,int fontSize,int window){
	Button button = Button(text,x,y,width,height,onClick,fontSize,window);
	buttons.push_back(button);
	return button;
}

Button UIManager::CreateButton(std::string imageFilePath,int relImgX,int relImgY,int imgWidth,int imgHeight,int x,int y,int width,int height,std::function<void(void)> onClick,int window){
	Button button = Button(imageFilePath,relImgX,relImgY,imgWidth,imgHeight,x,y,width,height,onClick,window);
	buttons.push_back(button);
	return button;
}

void UIManager::RemoveButton(Button button){
	if(!buttons.empty()){
		for(unsigned int i=0;i < buttons.size();i++){
			if(button.Equals(&buttons[i])){
				buttons.erase(buttons.begin() + i);
				return;
			}
		}
	}
}

TextField UIManager::CreateTextField(const char *text,int x,int y,int width,int height,std::function<void(std::string)> onTextUpdate,int fontSize,int window){
	TextField textField = TextField(text,x,y,width,height,onTextUpdate,fontSize,window);
	textFields.push_back(textField);
	return textField;
}

void UIManager::RemoveTextField(TextField textField){
	if(!textFields.empty()){
		for(unsigned int i=0;i < textFields.size();i++){
			if(textField.Equals(&textFields[i])){
				textFields.erase(textFields.begin() + i);
				return;
			}
		}
	}
}

TextBox UIManager::CreateTextBox(const char *buttonText,const char *fileFolder,std::string mode,int x,int y,std::function<void(std::string)> onEnter,std::function<bool(std::string)> onValidate,bool showFileName,int window){
	//TextBox textBox = TextBox(buttonText,text,x,y,onEnter,onValidate,window);
	TextBox textBox = TextBox(buttonText,fileFolder,mode,x,y,onEnter,onValidate,showFileName,window);
	textBoxes.push_back(textBox);
	return textBox;
}

void UIManager::RemoveTextBox(TextBox textBox){
	if(!textBoxes.empty()){
		for(unsigned int i=0;i < textBoxes.size();i++){
			if(textBox.Equals(&textBoxes[i])){
				textBoxes.erase(textBoxes.begin() + i);
				return;
			}
		}
	}
}

bool UIManager::IsOverUI(int mouseX,int mouseY){
	if(!buttons.empty()){
		for(Button button : buttons){
			if(mouseX >= button.GetX() && mouseX <= button.GetX()+button.GetWidth() && mouseY >= button.GetY() && mouseY <= button.GetY()+button.GetHeight()){
				return true;
			}
		}
	}
	if(!textFields.empty()){
		for(TextField textField : textFields){
			if(mouseX >= textField.GetX() && mouseX <= textField.GetX()+textField.GetWidth() && mouseY >= textField.GetY() && mouseY <= textField.GetY()+textField.GetHeight()){
				return true;
			}
		}
	}
	return false;
}
