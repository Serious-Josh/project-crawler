#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

class player{
    private:
        string name;
        int level;
        int hp, tempHp, mp, maxHp; //current values
        int str, mag, spd, end; //stats
        int currExp, needExp, totExp; //current exp, needed for next level exp, total exp
        bool guard;
        //weapon vector
        //armor vector
        //accessory vector
        //equipped weapon
        //equipped armor
        //equipped accessory
        //room* currRoom

    public:
        player(string name = "NULL"){

            //currFloor = 0;
            guard = false;

            srand(time(NULL));

            //random stat generation
            str = rand() % 12 + 1;
            mag = rand() % 12 + 1;
            spd = rand() % 12 + 1;
            end = rand() % 12 + 1;

            //standard initialiation
            this->name = name;
            level = 1;
            hp = 25 * end + 200; //used to have some needlessly complicated hp curve. simple +25 hp on level up
            mp = 10 * mag + 100; //same as hp. simple +10 mp on level up

            //currFloor = 0;
        }

        string getName(){
            return name;
        }
};