/*
** File: Terran.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Terran class
*/

#include "Terran.h"

// Name: Terran() - Default Constructor
// Description: Creates a new terran
// Preconditions: None
// Postconditions: Can create a terran
Terran::Terran(): Entity()
{
}
// Name: Terran(string name, int hp) - Overloaded constructor
// Description: Creates a new terran
// Preconditions: None
// Postconditions: Can be used to populate terran or child classes
Terran::Terran(string name, int hp): Entity(name, hp)
{
}
// Name: ~Terran - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Terran::~Terran()
{
}
// Name: Attack()
// Description: Describes attack statements for terran
// Preconditions: None
// Postconditions: Returns damage
int Terran::Attack()
{
    //generates random number (1-6)
    int damage = (rand() % 6) + 1;
    //displays normal attack with generated number as damage
    cout << GetName() << " attacks dealing " << damage << " damage." << endl;
    //returns damage
    return damage;
}
// Name: SpecialAttack()
// Description: Tells player that terran does not have special attack
// may be used for child class special attacks
// Preconditions: None
// Postconditions: May be used to call child class SpecialAttack
int Terran::SpecialAttack()
{
    //displays terran's special attack
    cout << GetName() << " has no special attack." << endl;
    //returns damage
    return 0;
}