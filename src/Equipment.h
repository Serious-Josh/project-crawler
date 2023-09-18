#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

//element enum type
enum class element {Fire, Ice, Earth, Forest, Wind, Normal};

//function to return string corresponding to element enum
string element_to_string(element type){
    switch (type){
        case element::Fire: return "Fire";
            break;
        case element::Ice: return "Ice";
            break;
        case element::Earth: return "Earth";
            break;
        case element::Forest: return "Forest";
            break;
        case element::Wind: return "Wind";
            break;
        case element::Normal: return "Normal";
            break;      
    }
}

//there used to be a randomPercentage function, but I don't see why I can't just use (rand() % 100)

//parent class for all equipment
class equipment{

    private:
        int weight, value;
        string name;
        double shopScaler;

    public:
        equipment(string name, int weight, int value, double shopScaler){
            this->name = name;
            this->weight = weight;
            this->value = value;
            this->shopScaler = shopScaler;
        }

        int getWeight(){
            return weight;
        }

        string getName(){
            return name;
        }

        int getValue(){
            return value;
        }

        void setName(string name){
            this->name = name;
        }

        void setValue(int val){
            value = val;
        }

        //placeholder for future setter methods
        //I don't think they're neccesary now, but they could be later on

        virtual string outputInfo() = 0;

};

enum class weaponType {Sword, Dagger, Spear, Axe, Bow};

string weapon_to_string(weaponType type){
    switch(type){
        case weaponType::Sword: return "Sword";
            break;
        case weaponType::Dagger: return "Dagger";
            break;
        case weaponType::Spear: return "Spear";
            break;
        case weaponType::Axe: return "Axe";
            break;
        case weaponType::Bow: return "Bow";
            break;
    }
}

int baseDmgCalc(weaponType type, int modifier, int shopScaler, element el){

    //temp here is used later on to prevent runaway damage values
    double temp = shopScaler * 0.8;
    int damage = 0;


    //original had a big complicated system with an additional scaler value, but I don't see the utility when there's already a shopScaler
    //this is actually probably the reason why I had insanely large damage values to begin with


    //weapon type damage generation. this is not remotely balanced, just want to get it working before actually putting thought into values
    switch(type){
        case weaponType::Sword: damage = ((rand() % 10 + 10) * shopScaler) * temp;
            break;
        case weaponType::Dagger: damage = ((rand() % 5 + 7) * shopScaler) * temp;
            break;
        case weaponType::Spear: damage = ((rand() % 12 + 11) * shopScaler) * temp;
            break;
        case weaponType::Axe: damage = ((rand() % 15 + 7) * shopScaler) * temp;
            break;
        case weaponType::Bow: damage = ((rand() % 7 + 14) * shopScaler) * temp;
            break;
    }

    //damage adjustment depending on weapon modifier (+1, +2, +3, +4, +5)
    switch(modifier){
        case 0: break;
        case 1: damage = damage * 1.1;
            break;
        case 2: damage = damage * 1.2;
            break;
        case 3: damage = damage * 1.3;
            break;
        case 4: damage = damage * 1.4;
            break;
        case 5: damage = damage * 1.5;
            break;
    }

    //I'm streamlining elemental damage here, can expand on it later on
    if(el != element::Normal){
        damage += 7;
    }

    return damage;
}

class weapon : public equipment {

    private:
        int dmg, dmgMod, shopScaler;
        element el;
        weaponType type;

    public:
        weapon(string name = "NULL", int weight = 0, int value = 0, int shopScaler = 1.0) : equipment(name, weight, value, shopScaler){

            this->shopScaler = shopScaler;

        //assinging whether the weapon has an element. 12% chance
            if((rand() % 101) <= 12){

                switch(int elType = (rand() % 5 + 1)){
                    case 1: el = element::Fire;
                        break;
                    case 2: el = element::Ice;
                        break;
                    case 3: el = element::Earth;
                        break;
                    case 4: el = element::Forest;
                        break;
                    case 5: el = element::Wind;
                        break;
                }
            }
            else{
                el = element::Normal;
            }

        //extremely lazy and shitty way of generating dmgMod
            if((rand() % 101) == 1){
                dmgMod = 5;
            }
            else if((rand() % 101) == 2){
                dmgMod = 4;
            }
            else if((rand() % 101) == 3){
                dmgMod = 3;
            }
            else if((rand() % 101) == 4 || 5){
                dmgMod = 2;
            }
            else if ((rand() % 101) == 6 || 7){
                dmgMod = 1;
            }
            else{
                dmgMod = 0;
            }

        //assinging weapon type and damage
            switch(rand() % 5 + 1){
                case 1: type = weaponType::Sword;
                        dmg = baseDmgCalc(type, dmgMod, shopScaler, el);
                    break;
                case 2: type = weaponType::Dagger;
                        dmg = baseDmgCalc(type, dmgMod, shopScaler, el);
                    break;
                case 3: type = weaponType::Spear;
                        dmg = baseDmgCalc(type, dmgMod, shopScaler, el);
                    break;
                case 4: type = weaponType::Axe;
                        dmg = baseDmgCalc(type, dmgMod, shopScaler, el);
                    break;
                case 5: type = weaponType::Bow;
                        dmg = baseDmgCalc(type, dmgMod, shopScaler, el);
                    break;
            }

        }

    //generating base information (name, value, weight)
        void generateInformation(){

        //name and value generation
        //using +30 value for elements
            if ((dmgMod > 0) && (el != element::Normal)){
                //has both modifier and element
                setName(weapon_to_string(type) + " of " + element_to_string(el) + " + " + to_string(dmgMod));
                setValue((dmg * 0.75) + 30 + (15 * dmgMod));
            }
            else if ((dmgMod > 0) && (el == element::Normal)){
                //has modifier but no element
                setName(weapon_to_string(type) + " + " + to_string(dmgMod));
                setValue((dmg * 0.75) + (15 * dmgMod));
            }
            else if ((dmgMod == 0) && (el != element::Normal)){
                //no modifier but has element
                setName(weapon_to_string(type) + " of " + element_to_string(el));
                setValue((dmg * 0.75) + 30);
            }
            else{
                //no modifier and no element
                setName(weapon_to_string(type));
                setValue(dmg * 0.75);
            }
        }
};