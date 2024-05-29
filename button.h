#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

//Button class definition
class Button {
private:
    bool pressed = false;
    Font font_;
    Text text_;
    RectangleShape rect;
    Color colour1_;
    Color colour2_;
    Vector2f mp;

public:
    Button(float x, float y, float w, float h, string content, Color colour1, Color colour2);

    bool isPressed(RenderWindow& win);

    void draw(RenderWindow& win);
};

#endif