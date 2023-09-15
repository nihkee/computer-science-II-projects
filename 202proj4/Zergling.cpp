/*
** File: Zergling.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Zergling class
*/

#include "Zergling.h"

// Name: Zergling() - Default Constructor
// Description: Creates a new Zergling type of zerg
// Preconditions: None
// Postconditions: Can create a Zergling
Zergling::Zergling(): Zerg()
{
}
// Name: Zergling(string name, int hp)
// Description: Creates a new Zergling
// Preconditions: None
// Postconditions: Can create a Zergling
Zergling::Zergling(string name, int hp): Zerg(name, hp)
{
}
// Name: SpecialAttack
// Description: Defines the Zergling's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Zergling::SpecialAttack()
{
    //displays zergling's special attack
    cout << GetName() << " scratches at you ferociously!" << endl;
    cout << "You take 1 point damage." << endl;
    //returns damage
    return 1;
}