/*
** File: Area.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Area class
*/

#include "Area.h"

//Name: Area (Overloaded Constructor)
//Precondition: Must have valid input for each part of a area
// First int is the unique identifier for this particular area.
// The first string is the name of the area
// The second string is the description of the area
// The last four ints are the unique identifier for adjacent areas (-1 = no path)
// North, East, South, and West
//Postcondition: Creates a new area
Area::Area(int identifier, string name, string desc, int north, int east, int south, int west)
{
  m_ID = identifier;
  m_name = name;
  m_desc = desc;
  m_direction[0] = north;
  m_direction[1] = east;
  m_direction[2] = south;
  m_direction[3] = west;
}
//Name: GetName
//Precondition: Must have valid area
//Postcondition: Returns area name as string
string Area::GetName()
{
  return m_name;
}
//Name: GetID
//Precondition: Must have valid area
//Postcondition: Returns area id as int
int Area::GetID()
{
  return m_ID;
}
//Name: GetDesc
//Precondition: Must have valid area
//Postcondition: Returns area desc as string
string Area::GetDesc()
{
  return m_desc;
}
//Name: CheckDirection
//Precondition: Must have valid area
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the area in that direction
//Postcondition: Returns id of area in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Area::CheckDirection(char myDirection)
{
  //returns id from m_direction array of respective direction
  switch (myDirection)
  {
    case 'N':
    case 'n':
        return m_direction[0];
    case 'E':
    case 'e':
        return m_direction[1];
    case 'S':
    case 's':
        return m_direction[2];
    case 'W':
    case 'w':
        return m_direction[3];
  }
  //returns -1 if user did not enter in valid input (n, N, e, E, s, S, w, W)
  return -1;
}
//Name: PrintArea
//Precondition: Area must be complete
//Postcondition: Outputs the area name, area desc, then possible exits
void Area::PrintArea()
{
  //prints area's details
  cout << m_name << endl;
  cout << m_desc << endl;
  cout << "Possible Exits: ";
  //displays directions that are valid (ids are not equal to -1)
  if (m_direction[0] != -1)
  {
    cout << "N";
  }
  else if (m_direction[1] != -1)
  {
    cout << "E";
  }
  else if (m_direction[2] != -1)
  {
    cout << "S";
  }
  else if (m_direction[3] != -1)
  {
    cout << "W";
  }
  cout << endl;
}

/*
 private:
  int m_ID; //Unique int for area number
  string m_name; //Name of area
  string m_desc; //Description of area
  int m_direction[4]; //Array holding area to north, east, south, west (-1 if no exit)
*/