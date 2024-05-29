#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "player.cpp"
#include "textdisplay.h"

using namespace std;
using namespace sf;

class Game {
private:
    //Delcare Private Attributes 
    TextDisplay Try;
    time_t displayTime = 0;
    bool score = false;
    Player Team1[5];
    Player Team2[5];
    bool tackle = false;
    char passDirection = 'r';

public:
    //Constructor Class
    //Initializes attributes and objects
    Game() :
        Try(640, 360, "TRY!!!", 120, "centred")
    {

        srand(time(NULL));

        for (int i = 0; i < 5; i++) {
            Team1[i] = Player(i + 1, 1);
        }

        for (int i = 0; i < 5; i++) {
            Team2[i] = Player(i + 6, 2);
        }

        Team1[0].ballCarrier = true;
    }

    //Calls all functions needed to be updated each frame and runs game logic
    bool run(RenderWindow& win) {
        //If player hasn't scored runs simulation logic
        if (score == false) {
            for (int i = 0; i < 5; i++) {

                //Check tackle data
                if (Team2[i].tackler == true) {
                    tackle = true;
                }

                if (Team2[i].tackler == true) {
                    if (Team2[i].ruck() == true) {
                        tackle = false;
                    }
                }

                if (tackle == false) {
                    Team2[i].ruckSpeed = time(0);
                }

                //Passing logic
                if (tackle == false) {
                    if (Team1[i].pass() == true) {
                        //Passing to the right
                        if (passDirection == 'r') {
                            if (i == 4) {
                                passDirection = 'l';
                            }
                            else {
                                Team1[i + 1].ballCarrier = true;
                                Team1[i + 1].timeWithBall = time(0);
                                Team1[i + 1].passTime = (rand() % 15 + 5.f) / 10;
                                Team1[i].ballCarrier = false;
                            }
                        }
                        //Passing to the left
                        if (passDirection == 'l') {
                            if (i == 0) {
                                passDirection = 'r';
                                Team1[i + 1].ballCarrier = true;
                                Team1[i + 1].timeWithBall = time(0);
                                Team1[i + 1].passTime = (rand() % 15 + 5.f) / 10;
                                Team1[i].ballCarrier = false;
                            }
                            else {
                                Team1[i - 1].ballCarrier = true;
                                Team1[i - 1].timeWithBall = time(0);
                                Team1[i - 1].passTime = (rand() % 15 + 5.f) / 10;
                                Team1[i].ballCarrier = false;
                            }
                        }

                    }
                }

                //Checks if scored
                if (Team1[i].ballCarrier) {
                    if (Team1[i].scored()) {
                        score = true;
                        displayTime = time(0);
                    }
                }

                //Move Players
                Team1[i].move(Team1, Team2, tackle);
                Team2[i].move(Team1, Team2, tackle);

                //Draw Players 
                win.draw(Team1[i].Rect);
                win.draw(Team2[i].Rect);
            }
        }

        //Runs scored messaged and ends the simulation
        else if (score) {
            if (time(0) - displayTime <= 5) {
                Try.draw(win);
            }
            else {
                return true;
            }
        }
        return false;

    }
};