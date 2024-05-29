#include <iostream>
#include <SFML/Graphics.hpp>

#include "win.cpp"
#include "titlescreen.cpp"
#include "login.cpp"
#include "game.cpp"

using namespace std;
using namespace sf;

const int TEAMSIZE = 5;

int main() {
    // Window Setup  //
    RenderWindow win(VideoMode(1280, 720), "Game Window");
    Win window;

    // Background Setup
    RectangleShape Bg(Vector2f(1000.f, 600.f));
    Bg.setPosition(140, 60);
    Bg.setFillColor(Color(60, 140, 60));

    int screen = 1;
    window.config("login");

    //  Game Part Setup  //
    Login login;
    TitleScreen titlescreen;
    Game game;
     
    //  Main Loop //
    while (win.isOpen()){

        // Event Based Checks and Decisions
        Event event;
        while (win.pollEvent(event)) {
            if (screen == 1) {
                login.usernameBox.update(event);
                login.passwordBox.update(event);
            }
            if (event.type == Event::Closed) {
                win.close();
            }
        }

        // Login Window
        if (screen == 1) {
            win.clear(Color(160, 160, 160));

            //Draw
            win.draw(window.BackGround);
            if (login.run(win)) {
                login.loggedIn = false;
                titlescreen.update(login.username);
                window.config("title");
                screen = 2;
            }
        }

        //TitleScreen Window
        else if (screen == 2) {
            win.clear(Color(50, 80, 250));

            //Draw
            win.draw(window.BackGround);
            if (titlescreen.run(win)) {
                window.config("game");
                screen = 3;
            }
            
        }

        //Game Window
        else if (screen == 3) {
            win.clear(Color(50, 50, 50));

            //Draw
            win.draw(window.BackGround);
            if (game.run(win)) {
                win.close();
            }
        }

        //Display
        win.display();
        win.setFramerateLimit(120);
    }

    return 0;
}