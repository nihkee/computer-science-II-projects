/*
** File: Mutalisk.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Mutalisk class
*/

#include "Mutalisk.h"

// Name: Mutalisk() - Default Constructor
// Description: Creates a new Mutalisk
// Preconditions: None
// Postconditions: Can create a Mutalisk
Mutalisk::Mutalisk()
{
}
// Name:  Mutalisk(string name, int hp)
// Description: Creates a new Mutalisk
// Preconditions: None
// Postconditions: Can create a Mutalisk
Mutalisk::Mutalisk(string name, int hp): Zerg(name, hp)
{
}
// Name: SpecialAttack
// Description: Defines the Mutalisk's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Mutalisk::SpecialAttack()
{
    //displays mutalisk's special attack
    cout << GetName() << " blasts you with their attack!" << endl;
    cout << "You take 4 points of damage." << endl;
    //returns damage
    return 4;
}