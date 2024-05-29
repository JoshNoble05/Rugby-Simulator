#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "textbox.cpp"
#include "textfile.cpp"

#include "button.h"
#include "textdisplay.h"

using namespace std;
using namespace sf;

class Login {
private:
	//Define private variables and objects
	string password;
	Button enter;
	Button newUser;
	TextFile Database;
	TextDisplay text_;

	//Verify users details
	void check(string type) {
		//Gets necessary data
		username = usernameBox.getText();
		password = passwordBox.getText();

		Database.read();

		//Checks login conditions
		if (type == "login") {
			for (int i = 0; i < 255; i++) {
				if (username == Database.database[i][0] && password == Database.database[i][1]) {
					loggedIn = true;
				}
			}
		}

		//Checks sign up conditions
		bool found = false;
		if (type == "sign up") {
			for (int i = 0; i < 255; i++) {
				if (username == Database.database[i][0]) {
					found = true;
				}
			}
			if (found == false) {
				update();
			}
		}

	}

public:
	//Define end condition
	bool loggedIn = false;

	//Define public objects
	Textbox usernameBox;
	Textbox passwordBox;
	string username;

	//Constructor class
	//Calls other objects constructors
	Login():
		text_(300, 130, "Login", 80, "default"),
		enter(300, 500, 200, 60, "Enter", Color(180, 180, 180), Color(150, 150, 150)),
		newUser(600, 500, 200, 60, "New User", Color(180, 180, 180), Color(150, 150, 150)),
		usernameBox(300, 280, "username"),
		passwordBox(300, 380, "password") {
	}

	bool run(RenderWindow &win) {
		//Check state / update textboxs
		usernameBox.check_active(win);
		passwordBox.check_active(win);

		//Draw objects
		usernameBox.draw(win);
		passwordBox.draw(win);
		enter.draw(win);
		newUser.draw(win);
		text_.draw(win);

		//Button detection and resolution
		if (enter.isPressed(win)) {
			check("login");
		}
		if (newUser.isPressed(win)) {
			check("sign up");
		}
		return loggedIn;
	}

	//Updates database with new user
	void update() {
		Database.writeNew(username, password);
		loggedIn = true;
	}
};