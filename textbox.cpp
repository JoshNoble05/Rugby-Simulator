#include <iostream>
#include <SFML/Graphics.hpp>

#include"textdisplay.h"

using namespace std;
using namespace sf;

class Textbox {
private:
	//Define objects
	TextDisplay titleText;
	TextDisplay userText;

	//Define private attributes
	Font font;
	int charLimit = 15;

public:

	//Defining public attributes
	string userInput = "";
	bool active = false;
	RectangleShape rect;
	Vector2f mp;

	//Constructor Class
	//Calls other objects constructors
	Textbox(float x, float y, string content):
	titleText(x, y - 50, content, 40, "default"),
	userText(x + 2, y + 2, "", 30, "default")
	{
		//Set TextBox
		rect.setSize(Vector2f(680, 40));
		rect.setPosition(Vector2f(x, y));
		rect.setFillColor(Color(220, 220, 220));
		rect.setOutlineThickness(5);
		rect.setOutlineColor(Color(120, 120, 120));
	}

	//Checks state of text box
	void check_active(RenderWindow &win) {
		mp = win.mapPixelToCoords(Mouse::getPosition(win));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (rect.getGlobalBounds().contains(mp.x, mp.y)){
				active = true;
			}

			else {
				active = false;
			}
		}
	}

	string getText() {
		return userInput;
	}

	// Draws textbox display
	void draw(RenderWindow& win) {
		win.draw(rect);
		titleText.draw(win);
		userText.draw(win);
	}

	// Updates the text to be displayed in the text box
	void update(Event event) {

		if (active) {
			if (event.type == Event::TextEntered) {
				if (isprint(event.text.unicode)) {
					userInput += event.text.unicode;
				}
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.scancode == Keyboard::Scan::Backspace) {
					if (!userInput.empty())
						userInput.pop_back();
				}
			}
			if (!(userInput.length() > charLimit)) {
				userText.update(userInput);
			}
			else {
				userInput.pop_back();
			}

			//Change textbox to active style
			rect.setFillColor(Color(220, 220, 220));
			rect.setOutlineColor(Color(80, 80, 80));
		}

		else if (active != true) {
			//Set textbox to default style
			rect.setFillColor(Color(220, 220, 220));
			rect.setOutlineColor(Color(120, 120, 120));
		}

		if (rect.getGlobalBounds().contains(mp.x, mp.y)) {
			//Set textbox to hover over style
			rect.setFillColor(Color(180, 180, 180));
		}
	}
};