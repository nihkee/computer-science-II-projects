/*
** File: Zerg.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Zerg class
*/

#include "Zerg.h"

// Name: Zerg() - Default Constructor
// Description: Would be used to create a zerg but abstracted
// Preconditions: None
// Postconditions: Used to populate child class data
Zerg::Zerg(): Entity()
{
}
// Name: Zerg(string name, int hp) - Overloaded Constructor
// Description: Would be used to create a Zerg but abstracted
// Preconditions: None
// Postconditions: Used to populate child class data
Zerg::Zerg(string name, int hp): Entity(name, hp)
{
}
// Name: Attack()
// Description: Describes attack statements for Zerg
// Preconditions: None
// Postconditions: Returns damage
int Zerg::Attack()
{
    //displays 
    cout << GetName() << " deals 1 point of damage." << endl;
    return 1;
}
// Name: SpecialAttack()
// Description: Purely virtual SpecialAttack
// Preconditions: None
// Postconditions: May be used to call child class SpecialAttack
//virtual int SpecialAttack()=0;