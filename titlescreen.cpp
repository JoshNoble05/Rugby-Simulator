#include <iostream>
#include <SFML/Graphics.hpp>

#include "button.h"
#include "textdisplay.h"

using namespace std;
using namespace sf;

class TitleScreen {
private:
    //Declare objects
    TextDisplay title_;
    Button start;

public:
    //Constructor class
    //Calls object parameterized constructors
    TitleScreen() :
        title_(640, 240, "Welcome Player", 80, "centred"),
        start(515, 400, 250, 100, "Start", Color(180, 180, 180), Color(150, 150, 150)) {}

    //Calls all functions needed to be updated each frame
    bool run(RenderWindow& win) {
        //Calls draw functions of all objects
        title_.draw(win);
        start.draw(win);

        //Check if button is pressed
        if (start.isPressed(win)) {
            return true;
        }
        return false;
    }

    //Update displayed text to have the user's username in
    void update(string username) {
        title_.update("Welcome " + username);
    }
};