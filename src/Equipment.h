#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

//element type enum
enum class element {Fire, Ice, Earth, Forest, Wind, Normal};

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

//weapon type enum
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

//material type enum
enum class material {Iron, Chainmail, Leather, Cloth};

string material_to_string(material type){
    switch(type){
        case material::Iron: return "Iron";
            break;
        case material::Chainmail: return "Chainmail";
            break;
        case material::Leather: return "Leather";
            break;
        case material::Cloth: return "Cloth";
            break;
    }
}

//armor type enum
enum class armorType {Helmet, Breastplate, Gauntlet, Boots};

string armor_to_string(armorType type){
    switch(type){
        case armorType::Helmet: return "Helmet";
            break;
        case armorType::Breastplate: return "Breastplate";
            break;
        case armorType::Gauntlet: return "Gauntlet";
            break;
        case armorType::Boots: return "Boots";
            break;
    }
}

//accessory type enum
enum class aType{HP, MP, Str, Mag, End, Spd};

string aType_to_string(aType type){
    switch(type){
        case aType::HP: return "HP";// +10% hp
            break;
        case aType::MP: return "MP";// +10% mp
            break;
        case aType::Str: return "Str";// +5 str
            break;
        case aType::Mag: return "Mag";// +5 mag
            break;
        case aType::End: return "End";// +5 end
            break;
        case aType::Spd: return "Spd";// +5 spd
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

        void setWeight(int weight){
            this->weight = weight;
        }

        string getName(){
            return name;
        }

        void setName(string name){
            this->name = name;
        }

        int getValue(){
            return value;
        }

        void setValue(int val){
            value = val;
        }

        //placeholder for future setter methods
        //I don't think they're neccesary now, but they could be later on

        virtual void generateInformation() = 0;

};

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

        //pretty lazy way of generating dmgMod
            switch(int temp = rand() % 100 + 1){
                case 1: dmgMod = 5;
                    break;
                case 2: dmgMod = 4;
                    break;
                case 3: dmgMod = 3;
                    break;
                case 4: case 5: dmgMod = 2;
                    break;
                case 6: case 7: dmgMod = 1;
                    break;
                default: dmgMod = 0;
                    break;
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

            generateInformation();
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
        
        int getDamage(){
            return dmg;
        }

        weaponType getType(){
            return type;
        }

        element getElement(){
            return el;
        }
};

class armor : public equipment {

    private:

    //going to investigate this tempArmor stat
        int armorStat, tempArmor;
        material mat;
        armorType type;

    public:
        armor(string name = "Null", int weight = 0, int value = 1, double shopScaler = 1.0): equipment(name, weight, value, shopScaler){

            int temp = (rand() % 100 + 1);
        //armorStat generation
            if(temp < 5){
                armorStat = (rand() % 56 * shopScaler);
            }
            else if(6 <= temp <= 10){
                armorStat = (rand() % 44 * shopScaler);
            }
            else if(11 <= temp <= 20){
                armorStat = (rand() % 32 * shopScaler);
            }
            else{
                armorStat = rand() % 20 * shopScaler;
            }



            generateInformation();
        }

        void generateInformation(){

        //type generation
            switch(rand() % 4 + 1){
                case 1: type = armorType::Helmet;
                    break;
                case 2: type = armorType::Breastplate;
                    break;
                case 3: type = armorType::Gauntlet;
                    break;
                case 4: type = armorType::Boots;
                    break;
            }

        //generating material and armor adjustement
        //I think I want material to be an enum type like weapon element


            switch(rand() % 4 + 1){
               case 1: mat = material::Iron;
                setArmor(getArmor() * 1.75);
                setValue(getArmor() * 0.8 + 30);
                    break;
                case 2: mat = material::Chainmail;
                setArmor(getArmor() * 1.5);
                setValue(getArmor() * 0.8 + 20);
                    break;
                case 3: mat = material::Leather;
                setArmor(getArmor() * 1.25);
                setValue(getArmor() * 0.8 + 10);
                    break;
                case 4: mat = material::Cloth;
                setValue(getArmor() * 0.8);
                    break;
            }

            setName(material_to_string(mat) + " " + armor_to_string(type));
            tempArmor = armorStat;
        }

        void setArmor(int armor){
            armorStat = armor;
        }

        int getArmor(){
            return armorStat;
        }

        void setTempArmor(int armor){
            tempArmor = armor;
        }

        int getTempArmor(){
            return tempArmor;
        }

        armorType getType(){
            return type;
        }

        material getMaterial(){
            return mat;
        }
};

class accessory : public equipment {

    private:
        aType type;

    public:
        accessory(string name = "NULL", int weight = 0, int value = 1, double shopScaler = 1.0): equipment(name, weight, value, shopScaler){

            generateInformation();

        }

        void generateInformation(){
        //generating type/name/value
        switch(rand() % 8 + 1){
            case 1: case 2: type = aType::HP;
                setName("Band of Health");
                    break;
            case 3: case 4: type = aType::MP;
                setName("Band of Aether");
                    break;
            case 5: type = aType::Str;
                setName("Ring of Power");
                    break;
            case 6: type = aType::Mag;
                setName("Ring of Spirit");
                    break;
            case 7: type = aType::End;
                setName("Ring of Vitality");
                    break;
            case 8: type = aType::Spd;
                setName("Ringo of Quickness");
                    break;
        }

            setValue(100);
        }

        aType getType(){
            return type;
        }
};