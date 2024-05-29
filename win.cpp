#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


//Class which sets the background of each major screen
class Win {
public:
	RectangleShape BackGround;

	//Checks which screen to configure the background too
	void config(string type) {
		if (type == "login") {
			loginWin();
		}
		if (type == "title") {
			titleWin();
		}
		if (type == "game") {
			gameWin();
		}
	}

private:
	//configures the backgrounds

	void loginWin() {
		BackGround.setPosition(Vector2f(100, 100));
		BackGround.setSize(Vector2f(1080, 520));
		BackGround.setFillColor(Color(140, 140, 140));
		BackGround.setOutlineColor(Color(80, 80, 80));
		BackGround.setOutlineThickness(20.f);
	}

	void titleWin() {
		BackGround.setPosition(140, 160);
		BackGround.setSize(Vector2f(1000.f, 500.f));
	}

	void gameWin() {
		BackGround.setPosition(140, 60);
		BackGround.setSize(Vector2f(1000.f, 600.f));
		BackGround.setFillColor(Color(60, 140, 60));
	}
};