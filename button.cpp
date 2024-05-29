#include <iostream>
#include <SFML/Graphics.hpp>

#include "button.h"

using namespace std;
using namespace sf;

//Constructor class
//Initalize attributes	
Button::Button(float x, float y, float w, float h, string content, Color colour1, Color colour2) {
	colour1_ = colour1;
	colour2_ = colour2;

	//Rect setup
	rect.setPosition(Vector2f(x, y));
	rect.setSize(Vector2f(w, h));
	rect.setFillColor(colour1_);

	//Set Font
	if (!font_.loadFromFile("../AovelSansRounded-rdDL.ttf")) {
		cout << "error loading font" << endl;
	}

	//Text setup
	text_.setFont(font_);
	text_.setString(content);
	text_.setPosition(x + ((w - text_.getGlobalBounds().width) / 2), y + ((h - text_.getGlobalBounds().height - 12) / 2));
	text_.setCharacterSize(30);
	text_.setFillColor(Color(0, 0, 0));
}

//Checks pressed condition
bool Button::isPressed(RenderWindow &win) {
	mp = win.mapPixelToCoords(Mouse::getPosition(win));
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (rect.getGlobalBounds().contains(mp.x, mp.y)) {
			rect.setFillColor(colour2_);
			pressed = true;
		}
	}

	if (pressed == true) {
		if (!(Mouse::isButtonPressed(Mouse::Left))) {
			rect.setFillColor(colour1_);
			pressed = false;
			return true;
				
		}
		else {
			return false;
		}
	}

	else {
		return false;
	}
}

//Draws button object
void Button::draw(RenderWindow& win) {
	win.draw(rect);
	win.draw(text_);
}