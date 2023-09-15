/*
** File: Marine.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Marine class
*/

#include "Marine.h"

// Name: Marine() - Default Constructor
// Description: Creates a new marine
// Preconditions: None
// Postconditions: Can create a marine
Marine::Marine():Terran()
{
}
// Name: Marine(string name, int hp)
// Description: Creates a new Marine
// Preconditions: None
// Postconditions: Can create a Marine
Marine::Marine(string name, int hp): Terran(name, hp)
{
}
// Name: ~Marine - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Marine::~Marine()
{
}
// Name: SpecialAttack
// Description: Defines the Marine's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Marine::SpecialAttack()
{
    //generates random number (1-8)
    int damage = (rand() % 8) + 1;
    //displays marine's special attack
    cout << GetName() << " spins up doing GATLING DAMAGE!" << endl;
    cout << GetName() << " deals " << damage << " damage." << endl;
    //returns damage
    return damage;
}