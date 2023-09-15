/*
** File: Battlecruiser.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Battlecruiser class
*/

#include "Battlecruiser.h"

// Name: Battlecruiser() - Default Constructor
// Description: Creates a new Battlecruiser
// Preconditions: None
// Postconditions: Can create a Battlecruiser
Battlecruiser::Battlecruiser()
{
}
// Name: Battlecruiser(string name, int hp)
// Description: Creates a new Battlecruiser
// Preconditions: None
// Postconditions: Can create a Battlecruiser
Battlecruiser::Battlecruiser(string name, int hp): Terran(name, hp)
{
}
// Name: ~Battlecruiser - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Battlecruiser::~Battlecruiser()
{
}
// Name: SpecialAttack
// Description: Defines the Battlecruiser's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Battlecruiser::SpecialAttack()
{
    //generates random number (3-12)
    int damage = (rand() % 10) + 3;
    //displays battlecruiser's special attack
    cout << GetName() << " uses the Yomato Cannon!" << endl;
    cout << GetName() << " deals " << damage << " damage." << endl;
    //returns damage
    return damage;
}