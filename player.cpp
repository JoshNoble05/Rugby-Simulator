#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib> 
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Player {
private:
	//Object Style Data
	Color teamColour;
	Color teamOutlineColour;

	//Private movement Data
	float targetX = 0;
	float targetY = 0;
	double baseSpeed = 0.8;
	float speed = 0;

	//Player setup
	void initPlayer() {

		srand(time(NULL));
		position_ = rand() % 99 + 1;

		//Team specific setup
		if (team_ == 1) {
			startX_ = float(400 - ((id_ - 1) * 40));
			startY_ = float(100 + ((id_ - 1) * 100));
			teamColour = Color(80, 100, 220, 255);
			teamOutlineColour = Color(40, 50, 110, 255);
		}

		else if (team_ == 2) {
			startX_ = 700.f;
			startY_ = 100 + ((id_ - 6) * 100);
			teamColour = Color(150, 30, 30, 255);
			teamOutlineColour = Color(75, 15, 15, 255);
		}

		//Calc Speed
		speedMod = (rand() % 10 + 5.f) / 10;
		speed = speedMod * baseSpeed;

	}

	//Collision check
	void collision(Player team1[5], Player team2[5], string axis) {
		//Check tackle collision
		for (int i = 0; i < 5; i++) {
			//Tackle collision
			if (Hitbox.getGlobalBounds().intersects(team1[i].Hitbox.getGlobalBounds())) {
				if (team1[i].ballCarrier && tackler == false) {
					tackleId = i;
					tackler = true;
					ruckSpeed = time(0);
				}
			}
		}

		//Check x collision
		if (axis == "x") {
			for (int i = 0; i < 5; i++) {
				if (team2[i].id_ == id_) {
					i++;
				}
				else if (Hitbox.getGlobalBounds().intersects(team2[i].Hitbox.getGlobalBounds())) {
					if (Hitbox.getPosition().x > team2[i].Hitbox.getPosition().x) {
						Hitbox.setPosition(Vector2f(team2[i].Hitbox.getPosition().x + team2[i].Hitbox.getSize().x, Hitbox.getPosition().y));
					}
					else if (Hitbox.getPosition().x < team2[i].Hitbox.getPosition().x) {
						Hitbox.setPosition(Vector2f(team2[i].Hitbox.getPosition().x - Hitbox.getSize().x, Hitbox.getPosition().y));
					}
				}
			}
		}

		//Check y collision
		if (axis == "y") {
			for (int i = 0; i < 5; i++) {
				if (team2[i].id_ == id_) {
					i++;
				}
				else if (Hitbox.getGlobalBounds().intersects(team2[i].Hitbox.getGlobalBounds())) {
					if (Hitbox.getPosition().y > team2[i].Hitbox.getPosition().y) {
						Hitbox.setPosition(Vector2f(Rect.getPosition().x, team2[i].Hitbox.getPosition().y + team2[i].Rect.getSize().y));
					}
					else if (Hitbox.getPosition().y < team2[i].Hitbox.getPosition().y) {
						Hitbox.setPosition(Vector2f(Rect.getPosition().x, team2[i].Hitbox.getPosition().y - Rect.getSize().y));
					}
				}
			}
		}

	}
	// Calculate target coords
	void getTargetMove(Player team1[5], Player team2[5], bool tackle) {

		//Delcare local variables
		int ballCarrierId = 0;
		int tacklerId = 0;
		int playerId = 0;

		//Define local variables
		for (int i = 0; i < 5; i++) {
			if (team1[i].ballCarrier == true) {
				ballCarrierId = i;
			}
			if (team2[i].tackler == true) {
				tacklerId = i;
			}
			if (team1[i].id_ == id_) {
				playerId = i;
			}
			if (team2[i].id_ == id_) {
				playerId = i;
			}
		}

		//Checks stage of the game and team the player is on to determine where the player needs to move to
		if (tackle == true) {
			if (team_ == 1) {
				if (playerId > ballCarrierId) {
					targetX = team1[ballCarrierId].Hitbox.getPosition().x + ((ballCarrierId - playerId) * 20);
				}
				else if (playerId < ballCarrierId) {
					targetX = team1[ballCarrierId].Hitbox.getPosition().x + ((playerId - ballCarrierId) * 30);
				}
				targetY = team1[ballCarrierId].Hitbox.getPosition().y + ((playerId - ballCarrierId) * 100);
			}

			else if (team_ == 2) {
				if (tacklerId != playerId) {
					targetX = team2[tacklerId].Hitbox.getPosition().x + 60;
					targetY = team2[tacklerId].Hitbox.getPosition().y + (playerId - tacklerId) * 100;
				}
				else if (tacklerId == playerId) {
					targetX = team1[ballCarrierId].Hitbox.getPosition().x + 50;
					targetY = team1[ballCarrierId].Hitbox.getPosition().y;
				}
			}
		}

		else if (tackle == false) {
			targetX = team1[ballCarrierId].Hitbox.getPosition().x + 30;
			targetY = team1[ballCarrierId].Hitbox.getPosition().y;
		}
	}

public:

	//Game objects
	RectangleShape Hitbox;
	RectangleShape Rect;

	//Public player Data
	int id_;
	int team_;
	int position_;
	bool ballCarrier = false;
	int ballCarrierId = 0;
	bool tackler = false;
	double passTime = 0.5;
	double ruckTime = 1;
	int tackleId = 0;
	time_t timeWithBall = time(0);
	time_t ruckSpeed = time(0);
	float speedMod;
	float startX_ = 100;
	float startY_ = 100;

	//Parameterized constructor class
	//Defines and initalized all player data/variables
	Player(int id, int team) :
		id_(id), team_(team)
	{
		initPlayer();

		//Set Rect Data
		Rect.setOutlineThickness(4.f);
		Rect.setFillColor(teamColour);
		Rect.setOutlineColor(teamOutlineColour);
		Rect.setSize(Vector2f(30.f, 60.f));
		Rect.setPosition(startX_, startY_);

		//Set Hitbox Data
		Hitbox.setSize(Vector2f(30.f, 60.f));
		Hitbox.setPosition(startX_, startY_);
	}

	//Default constructor class
	Player(){
		id_ = 0;
		team_ = 0;
		
		initPlayer();
	}

	//Pass condition check
	bool pass() {
		if (ballCarrier == true) {
			Rect.setOutlineColor(Color(0, 0, 0, 255));
			if (time(0) - timeWithBall >= passTime) {
				ballCarrier = false;
				return true;
			}
		}
		else{
			Rect.setOutlineColor(teamOutlineColour);
			timeWithBall = time(0);
		}
		return false;
	}

	//Ruck condition check
	bool ruck() {
		if (tackler == true) {
			if (time(0) - ruckSpeed >= ruckTime) {
				tackler = false;
				return true;
			}
		}
		else {
			ruckSpeed = time(0);
			return false;
		}
		
	}

	//Move Player
	void move(Player team1[5], Player team2[5], bool tackle) {

		//Declare local variables
		float changeX;
		float changeY;
		float xSpeed;
		float ySpeed;
		float magnitude;
		float scaleFactor;

		//Define ballCarrierId
		for (int i = 0; i < 5; i++) {
			if (team1[i].ballCarrier == true) {
				ballCarrierId = i;
			}
		}

		//Checks game state and player data to decide how to move the players
		if (team_ == 1 && tackle == false) {
			if (Hitbox.getPosition().x + 10 <= team1[ballCarrierId].Hitbox.getPosition().x || team1[ballCarrierId].id_ == id_) {
				xSpeed = speed;
				Hitbox.move(xSpeed, 0);
				Rect.setPosition(Hitbox.getPosition());
			}
			else {
				xSpeed = speed;
				Hitbox.move(-xSpeed, 0);
				Rect.setPosition(Hitbox.getPosition());
			}
		}
		//Main movement algorithm
		else if (team1[ballCarrierId].id_ != id_) {
			//Get coodrs of objects
			getTargetMove(team1, team2, tackle);

			Vector2f playerPos = Hitbox.getPosition();

			//Cacl speed and direction

			changeX = targetX - playerPos.x;
			changeY = targetY - playerPos.y;

			magnitude = float(sqrt(pow(changeX, 2) + pow(changeY, 2)));
			scaleFactor = magnitude / speed;

			xSpeed = changeX / scaleFactor;
			ySpeed = changeY / scaleFactor;

			//Move and check for colisions if necessary
			if (team_ == 1) {
				Hitbox.move(xSpeed, 0);
				Hitbox.move(0, ySpeed);
			}
			else if (team_ == 2) {
				Hitbox.move(xSpeed, 0);
				collision(team1, team2, "x");
				Hitbox.move(0, ySpeed);
				collision(team1, team2, "y");
			}

			Rect.setPosition(Hitbox.getPosition());
		}
	}
	
	//Check scored condition
	bool scored() {
		if (Rect.getPosition().x >= 1100) {
			return true;
		}
		return false;
	}
};