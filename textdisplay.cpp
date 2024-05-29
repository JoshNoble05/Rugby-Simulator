#include <iostream>
#include <SFML/Graphics.hpp>

#include "textdisplay.h"

using namespace std;
using namespace sf;

//Set Font
void TextDisplay::initFont() {
	if (!font_.loadFromFile("../AovelSansRounded-rdDL.ttf")) {
		cout << "error loading font" << endl;
	}
}

//Text setup using inputted values
void TextDisplay::initText() {
    text_.setFont(font_);
    text_.setString(content_);
    text_.setCharacterSize(fontSize_);
    text_.setFillColor(Color(0, 0, 0));
    if (type_ == "default") {
        text_.setPosition(x_, y_);
    }
    else if (type_ == "centred") {
        text_.setPosition(x_ - ((text_.getGlobalBounds().width) / 2), y_ - (text_.getGlobalBounds().height / 2));
    }
    
}

//Parameterize constructor class
//Sets text information and calls initalizing functions
TextDisplay::TextDisplay(float x, float y, const string content, int size, string type):
    x_(x), y_(y), content_(content), fontSize_(size), type_(type)
{
    initFont();
    initText();
}

//Default constructor class
TextDisplay::TextDisplay() {
    content_ = "Hello World";
    x_ = 0;
    y_ = 0;
    fontSize_ = 40;

    initFont();
    initText();

}

//Draws text
void TextDisplay::draw(RenderWindow& win) {
    win.draw(text_);
}

//Updates content and re-initalized the text
void TextDisplay::update(string content) {
    content_ = content;
    initText();
}
