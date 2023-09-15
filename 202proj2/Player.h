//Title: Player.h
//Author: Jeremy Dixon
//Date: 9/20/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC
//This class is used to keep information about the human player (not computer)

#ifndef PLAYER_H //Include/Header Guard
#define PLAYER_H //Include/Header Guard

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// constants
const int MAX_STAT = 10; //Maximum of any player stat
const int START_STAT = 1; //Starting value of all stats
const int NUM_STATS = 3; //Number of stats for game (speed, agility, jump)

// class - do not add any functions to project 2
class Player{
 public:
  // Name: Player() - Default Constructor
  // Desc: Used to build a new Player
  // Preconditions - Requires default values
  // Postconditions - Creates new Player (with default name of "Beannie" with 1 speed/agility/jump
  Player();
  // Name: Player(name) - Overloaded constructor
  // Desc - Used to build a new Player
  // Preconditions - Requires name
  // Postconditions - Creates a new Player (with passed name and 1 speed/agility/jump)
  // May not be used in the project explicitly but please implement
  Player(string name);
  // Name: GetName()
  // Desc - Getter for Player name
  // Preconditions - Player exists
  // Postconditions - Returns the name of the Player
  string GetName();
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Player
  // Preconditions - Player exists
  // Postconditions - Sets name of Player
  void SetName(string name);
  // Name: GetSpeed
  // Desc - Gets the speed from this player
  // Preconditions - Player has a speed assigned
  // Postconditions - Returns the speed of the player
  int GetSpeed();
  // Name: GetAgility
  // Desc - Gets the agility from this player
  // Preconditions - Player has a agility assigned
  // Postconditions - Returns the agility of the player
  int GetAgility();
  // Name: GetJump
  // Desc - Gets the jump from this player
  // Preconditions - Player has a jump assigned
  // Postconditions - Returns the jump of the player
  int GetJump();
  // Name: GetRaces
  // Desc - Gets the total number of races the player has run
  // Preconditions - Player has a races assigned
  // Postconditions - Returns the total number of races run
  int GetRaces();
  // Name: GetFalls
  // Desc - Gets the total number of falls for the player
  // Preconditions - None
  // Postconditions - Returns the total falls for the player
  int GetFalls();
  // Name: SetRaces
  // Desc - Sets the total number of races the player has run
  // Preconditions - None
  // Postconditions - Sets total number of races run
  void SetRaces(int races);
  // Name: SetFalls
  // Desc - Sets the total number of falls for the player
  // Preconditions - None
  // Postconditions - Sets the total falls for the player
  void SetFalls(int falls);
  // Name: DisplayStatus
  // Desc - Displays the player names and their stats
  // Precondition - None
  // Postconditions - Displays the player information
  void DisplayStatus();
  // Name: IncreaseStat
  // Desc - Asks the user for a stat to increase (speed, agility, or jump) up to a max of 10
  // Precondition - Called after winning a race
  // Postconditions - Increases one stat by one point (max 10)
  void IncreaseStat();
  // Name: GetStat
  // Desc - Returns the value of a stat at a specific location (0 = speed, 1 = agility, 2 = jump)
  // Precondition - None
  // Postconditions - Returns the integer value of a specific stat
  int GetStat(int stat);
  // Name: IncreaseWins
  // Desc - Increases the number of wins by 1
  // Precondition - None
  // Postconditions - Increases the number of wins by 1
  void IncreaseWins();
private:
  string m_name; //Name of Player
  int m_stat[3]; //Stats of player: 0 = speed, 1 = agility, 2 = jump
  int m_races; //Starts at 0
  int m_wins; //Starts at 0
  int m_falls; //Starts at 0
};

#endif //Exit Header Guard
