#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Player.h"

using namespace std;

int main(){

    //initializing seed with current time
    srand(time(NULL));

    //variable for initial generation ie. if program has launched before, don't generate things again
    bool startUp = true;


    cout << "Hi there! I'm Felix and I'll be your furr-ocious feline companion on your adventure! Been a while since I've helped an adventurer, but you'll see I'm quite the cat-ch!" << endl;
    cout << "What's your name stranger?" << endl;

    //user enters name
    string name;
    cin >> name;
    player* play = new player(name);

    system("CLS");

    cout << play->getName() << " huh... I'll be honest, I thought it would be much more nyarly and intimidating, but I suppose " << play->getName() << " will do. Come on!" << endl;

    system("PAUSE");
	system("CLS");

    return 0;
}