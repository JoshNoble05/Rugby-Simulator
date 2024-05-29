#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


//Text Display class definition
class TextDisplay {
private:
    Font font_;
    string content_;
    float x_;
    float y_;
    int fontSize_;
    string type_;

    void initFont();

    void initText();

public:
    Text text_;

    TextDisplay(float x, float y, string content, int size, string type);

    TextDisplay();

    void draw(RenderWindow& win);

    void update(string content);
};

#endif