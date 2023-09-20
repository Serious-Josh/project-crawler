#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "Equipment.h"

using namespace std;

class player{
    private:
        string name;
        int level;
        int hp, maxHP, mp, maxMP; //current values
        int str, mag, spd, end; //stats
        int currExp, needExp, totExp; //current exp, needed for next level exp, total exp
        int damage, tempDamage; //I believe this is essentially an incoming damage buffer system
        bool guard, hasArmor, hasAcc;
        vector<weapon*> weapons;
        vector<armor*> armors;
        vector<accessory*> accessories;
        weapon* playerWeapon; //equipped weapon
        armor* playerArmor; //equipped armor
        accessory* playerAccessory; //equipped accessory
        //room* currRoom
        //bool bossKill

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

        int getTempDamage(){
            return tempDamage;
        }

        void setTempDamage(int temp){
            tempDamage = temp;
        }

        int getDamage(){
            return damage;
        }

        void setDamage(int dam){
            damage = dam;
        }

        string getName(){
            return name;
        }

        void setName(string name){
            this->name = name;
        }

        int getMaxHP(){
            return maxHP;
        }

        void setMaxHP(int hp){
            maxHP = hp;
        }

        void unequipAccessory(){
            if(hasAcc){
        //logic for removing accessory bonus
                switch(playerAccessory->getType()){
                    case aType::HP: maxHP = maxHP / 0.9;
                        break;
                    case aType::MP: maxMP = maxMP / 0.9;
                        break;
                    case aType::Str: str -= 5;
                        break;
                    case aType::Mag: mag -= 5;
                        break;
                    case aType::End: end -= 5;
                        break;
                    case aType::Spd: spd -= 5;
                        break;
                }
            }
        }

        void equipAccessory(accessory* newAcc){

            unequipAccessory();
            this->playerAccessory = newAcc;

            switch(newAcc->getType()){
                case aType::HP: maxHP = maxHP * 1.1;
                        break;
                    case aType::MP: maxMP = maxMP * 1.1;
                        break;
                    case aType::Str: str += 5;
                        break;
                    case aType::Mag: mag += 5;
                        break;
                    case aType::End: end += 5;
                        break;
                    case aType::Spd: spd += 5;
                        break;
            }
        }

        void addAccessory(accessory* newA){
            accessories.push_back(newA);
        }

        void gainExp(int exp){
            totExp += exp;

            if(exp > needExp){
                currExp = exp - needExp;
                level++;

                maxHP += (rand() % 100 + 1) + (4 * end);
                maxHP += (rand() % 20 + 1) + (2 * mag);
                str += rand() % 3 + 1;
                mag += rand() % 3 + 1;
                end += rand() % 3 + 1;
                spd += rand() % 3 + 1;
            }
            else{
                currExp += exp;
            }
        }

        void outputWeapons(){

            if(playerWeapon != NULL){
                //showing currently equipped armor to compare against
                cout << "Currently Equipped: " << playerWeapon->getName() << " - " << playerWeapon->getDamage() << " Attack" << endl << endl << "Inventory: " << endl;
            }
            else{
                cout << "No equipped weapons" << endl << endl << "Inventory: " << endl;
            }

            if(weapons.size() != 0){
                for(unsigned int i = 1; (i - 1) < weapons.size(); i++){
                    cout << 1 << ". " << weapons[(i - 1)]->getName() << " - " << weapons[(i - 1)]->getDamage() << " Attack" << endl;
                }
            }
            else{
                cout << "You have nothing else in your inventory." << endl;
            }
        }

        //outputAccess()

};