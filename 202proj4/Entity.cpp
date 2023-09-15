/*
** File: Entity.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Entity class
*/

#include "Entity.h"

// Name: Entity() - Default Constructor
// Description: Abstract class - cannot directly instantiate this class
// Preconditions: None
// Postconditions: Populates variables used in child classes (may not be specifically used)
Entity::Entity()
{
    m_name = "";
    m_health = 0;
}
// Name: Entity(string name , int health) - Overloaded Constructor
// Description: Abstract class - cannot directly instantiate this class
// Preconditions: None
// Postconditions: Populates variables used in child classes
Entity::Entity(string name, int health)
{
    m_name = name;
    m_health = health;
}
// Name: virtual ~Entity - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Entity::~Entity()
{
}
// Name: GetName()
// Description: Returns name of entity
// Preconditions: Entity has name
// Postconditions: None
string Entity::GetName()
{
    return m_name;
}
// Name: GetHealth()
// Description: Returns health of entity
// Preconditions: Entity has health
// Postconditions: None
int Entity::GetHealth()
{
    return m_health;
}
// Name: SetName()
// Description: Sets name of entity
// Preconditions: None
// Postconditions: Name is set
void Entity::SetName(string n)
{
    m_name = n;
}
// Name: SetHealth()
// Description: Sets health of entity
// Preconditions: None
// Postconditions: Health is set
void Entity::SetHealth(int h)
{
    m_health = h;
}
// Name: Attack()
// Description: Defines attack for an entity
// Preconditions: None
// Postconditions: None (Purely virtual - must be in child classes)
//virtual int Attack() = 0;
// Name: SpecialAttack()
// Description: Defines special attack for an entity
// Preconditions: None
// Postconditions: None (Purely virtual - must be in child classes)
//virtual int SpecialAttack() = 0;
// Name: Overloaded <<
// Description: Prints the details of an entity
// Preconditions: all variables are set valid
// Postconditions: returns an ostream with output of entity


/*
private:
  string m_name; //Name of entity
  int m_health; //Health of entity
*/