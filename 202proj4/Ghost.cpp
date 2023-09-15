/*
** File: Ghost.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Ghost class
*/

#include "Ghost.h"

// Name: Ghost() - Default Constructor
// Description: Creates a new Ghost
// Preconditions: None
// Postconditions: Can create a Ghost
Ghost::Ghost(): Terran()
{
}
// Name: Ghost(string name, int hp)
// Description: Creates a new Ghost
// Preconditions: None
// Postconditions: Can create a Ghost
Ghost::Ghost(string name, int hp): Terran(name, hp)
{
}
// Name: ~Ghost - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Ghost::~Ghost()
{
}
// Name: SpecialAttack
// Description: Defines the Ghost's special attack
// Preconditions: None
// Postconditions: Returns damage from special attack
int Ghost::SpecialAttack()
{
    //generates random number (2-12)
    int damage = (rand() % 11) + 2;
    //displays ghost's special attack
    cout << GetName() << " performs a sneak attack!" << endl;
    cout << GetName() << " deals " << damage << " damage." << endl;
    //returns damage
    return damage;
}