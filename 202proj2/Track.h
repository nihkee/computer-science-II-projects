//Title: Track.h
//Author: Jeremy Dixon
//Date: 9/29/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC

#ifndef TRACK_H //Include/Header Guard
#define TRACK_H //Include/Header Guard

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Constants
const int NUM_RACERS = 4; //Default number of players (1 human and 3 computer)
const int DEFAULT_LENGTH = 4; //Default starting length of a race
const int MAX_LENGTH = 100; //Maximum length of a race
const string OBSTACLE_TYPE[3] = {"speed", "agility", "jump"}; //Word descriptions of the three types of obstacles

// class - do not add any functions to project 2
class Track{
 public:
  // Name: Track() - Default Constructor
  // Desc: Used to build a new Track with default length 4
  // Sets track so that all players start in position 0
  // Preconditions - Requires default values
  // Postconditions - Creates new Track with a default length 4 and each m_track = 0
  Track();
  // Name: SetLength
  // Desc - Sets the length of the track
  // Preconditions - Requires length
  // Postconditions - Sets the length of the track
  void SetLength(int length);
  // Name: PopulatsObstacles()
  // Desc - For each length of track, assigns random type of obstacle (speed, agility, jump)
  //        Uses integers (0 = speed, 1 = agility, 2 = jump)
  // Preconditions - Track exists
  // Postconditions - Populates m_obstacle with random number between 0 and 2
  void PopulateObstacles();
  // Name: GetStatus()
  // Desc - Returns the status of race
  // Preconditions - Track exists
  // Postconditions - Outputs where each racer is in track and the type of obstacle
  void GetStatus();
  // Name: CheckWin()
  // Desc - Checks to see if the race is over by comparing each racer's
  //        location to the length of the track.
  //        Returns number of player who wins race (always starts at 0 first)
  // Preconditions - Track exists
  // Postconditions - Returns integer location of winner (0 is human). Always returns human in case of tie!
  int CheckWin();
  // Name: GetObstacle
  // Desc - Returns the integer of the obstacle at a specific location
  // Preconditions - Track exists
  // Postconditions - Returns 0 for speed, 1 for agility, and 2 for jump
  int GetObstacle(int location);
  // Name: IncrementLocation
  // Desc - Increments the m_track value for a specific player the human player
  //        is always in position 0
  // Preconditions - Race starts with everyone having a 0
  // Postconditions - Increases the integer value for a specific player
  void IncrementLocation(int player);
  // Name: ResetLocation
  // Desc - Before each race, resets the starting location for all players back to 0
  // Preconditions - Track exists
  // Postconditions - All players has a starting location of 0 in the m_track
  void ResetLocation();
  // Name: ConvertObstacle
  // Desc - Returns the string name of the obstacle using the OBSTACLE_TYPE
  //        array for a specific player
  // Preconditions - Player exists in m_track
  // Postconditions - Pulls the location from m_track for a provided player
  //                  then returns the obstacle at that location
  string ConvertObstacle(int player);
private:
  int m_track[NUM_RACERS]; //Location of each racer on track
  int m_length; //Length of track
  int m_obstacle[MAX_LENGTH]; //Type of obstacle in part of track (0=speed, 1=agility, 2=jump)
};

#endif //Exit Header Guard
