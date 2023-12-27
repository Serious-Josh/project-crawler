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


    //accesory functions
        void addAccessory(accessory* newA){
            accessories.push_back(newA);
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

                hasAcc = false;
            }
            else{
                cout << "You have no accessory currently equipped." << endl;
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

        //I believe originally I planned on having most actions be 'command line' functions and no interactable gui, which is why this function exists
        void swapAccessory(){

            unsigned int newAcc;

            if(accessories.empty()){
                cout << "You have no accessories to swap to." << end;
            }
            else{
                cout << endl << "What accessory would you like to swap to?" << end;
                cin >> newAcc;

                //logic for remvoing previously equipped accessory bonuses
                switch(playerAccessory->getType()){
                
                case aType::HP:
                   maxHP = maxHP / 1.1;
                   break;
                case aType::MP:
                    maxMP = maxMP / 1.1;
                    break;
                case aType::Str:
                    str -= 5;
                    break;
                case aType::Mag:
                    mag -= 5;
                    break;
                case aType::End:
                    end -= 5;
                    break;
                case aType::Spd:
                    spd -= 5;
                    break;
            }

            accessories.push_back(playerAccessory);
            equipAccessory(accessories[(newAcc - 1)]);
            //this removes the newly equipped item from the inventory
            accessories.erase(accessories.begin() + (newAcc - 1));
        }
        }

        void outputAccess(){
            if(accessories.size() != 0){
                for (int i = 1; (i - 1) < accessories.size(); i++){
                    cout << i << ". " << accessories[(i - 1)]->getName() << " - +" << accessories[(i - 1)]->outputInfo() << endl;
                }
            }
            else{
                cout << "You have no accessories in your inventory." << endl;
            }
        }


    //weapon functions
        void addWeapon(weapon* weapon){
            weapons.push_back(weapon);
        }

        void unequipWeapon(){
            equipWeapon(new weapon("Fists", 0, 0, 0));
        }

        void equipWeapon(weapon* weapon){
            playerWeapon = weapon;
        }

        void swapWeapons(){

            unsigned int newWeapon;

            if(weapons.empty()){
                cout << "You have no weapon to swap to." << endl << endl;
                system("PAUSE");
            }
            else{

                cout << endl << "What weapon would you like to equip?" << endl;
                cin >> newWeapon;

                weapons.push_back(playerWeapon);
                equipWeapon(weapons[(newWeapon - 1)]);
                weapons.erase(weapons.begin() + (newWeapon - 1));
            }
        }

        void outputWeapons(){

            if(playerWeapon != NULL){
                //showing currently equipped weapon to compare against
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

        //armor functions
        void addArmor(armor* armor){
            armors.push_back(armor);
        }

        void unequipArmor(){
            playerArmor = NULL;
            hasArmor = false;
        }

        void equipArmor(armor* armor){
            playerArmor = armor;
            hasArmor = true;
        }

        void swapArmor(){

            unsigned int newArmor;

            if(armors.empty()){
                cout << "You have no armor to swap to." << endl << endl;
                system("PAUSE");
            }
            else{
                cout << endl << "What armor would you like to equip?" << endl;
                cin >> newArmor;
                
                armors.push_back(playerArmor);
                equipArmor(armors[(newArmor - 1)]);
                armors.erase(armors.begin() + (newArmor - 1));
            }
        }

        void outputArmor(){

            //showing currently equipped armor to compare against
            cout << "Currently Equipped: " << playerArmor->getName() << " - " << playerArmor->getArmor() << " Armor" << endl << endl << "Inventory: " << endl;

            if(armors.size() != 0){
                for(int i = 1; (i - 1) < armors.size(); i++){
                    cout << i << ". " << armors[(i - 1)]->getName() << " - " << armors[(i - 1)]->outputInfo() << "Armor" << endl;
                }
            }
            else{
                cout << "You have nothing else in your inventory." << endl;
            }
        }
};