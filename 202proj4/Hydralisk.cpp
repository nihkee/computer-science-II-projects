/*
** File: Hydralisk.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Hydralisk class
*/

#include "Hydralisk.h"

// Name: Hydralisk() - Default Constructor
// Description: Creates a new Hydralisk
// Preconditions: None
// Postconditions: Can create a Hydralisk
Hydralisk::Hydralisk()
{
}
// Name: Hydralisk(string name, int hp)
// Description: Creates a new Hydralisk
// Preconditions: None
// Postconditions: Can create a Hydralisk
Hydralisk::Hydralisk(string name, int hp): Zerg(name, hp)
{
}
// Name: SpecialAttack
// Description: Defines the Hydralisk's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Hydralisk::SpecialAttack()
{
    //displays hydralisk's special attack
    cout << GetName() << " sprays you with deadly acid!" << endl;
    cout << "You take 2 point of damage." << endl;
    //returns damage
    return 2;
}