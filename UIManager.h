#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include "UI/Button.h"
#include "UI/TextField.h"
#include "UI/TextBox.h"
#include "SpriteManager.h"
#include <vector>
#include <string>
#include <functional>

class Button;
class TextField;
class TextBox;

class UIManager {
public:
	~UIManager();

	void Start(void);
	void Update(SDL_Event *event);
	void End(void);

	static UIManager &GetInstance(void);

	Button CreateButton(const char *text,int x,int y,int width,int height,std::function<void(void)> onClick,int fontSize = 23,int window = 0);
	Button CreateButton(std::string imageFilePath,int relImgX,int relImgY,int imgWidth,int imgHeight,int x,int y,int width,int height,std::function<void(void)> onClick,int window = 0);
	void RemoveButton(Button button);

	TextField CreateTextField(const char *text,int x,int y,int width,int height,std::function<void(std::string)> onTextUpdate,int fontSize = 23,int window = 0);
	void RemoveTextField(TextField textField);

	TextBox CreateTextBox(const char *buttonText,const char *fileFolder,std::string mode,int x,int y,std::function<void(std::string)> onEnter,std::function<bool(std::string)> onValidate,bool showFileName,int window);
	void RemoveTextBox(TextBox textBox);

	bool IsOverUI(int mouseX,int mouseY);
private:
	UIManager();

	std::vector<Button> buttons;

	std::vector<TextField> textFields;
	int prevTypingTextField;

	std::vector<TextBox> textBoxes;
};

#endif
