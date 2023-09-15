/*
** File: Track.cpp
** Assignment Name: Project 2 – UMBC Racer
** Author: Nikki Cayas
** Date: 10/6/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Track class
*/
#include "Track.h"

/*
Constants:
const int NUM_RACERS = 4; //Default number of players (1 human and 3 computer)
const int DEFAULT_LENGTH = 4; //Default starting length of a race
const int MAX_LENGTH = 100; //Maximum length of a race
const string OBSTACLE_TYPE[3] = {"speed", "agility", "jump"}; //Word descriptions of the three types of obstacles
*/

// Name: Track() - Default Constructor
// Desc: Used to build a new Track with default length 4
// Sets track so that all players start in position 0
// Preconditions - Requires default values
// Postconditions - Creates new Track with a default length 4 and each m_track = 0
Track::Track()
{  
    //sets length to default length
    m_length = DEFAULT_LENGTH;
    //sets all player positions to 0
    for (int i = 0; i < NUM_RACERS; i++)
    {
        m_track[i] = 0;
    }
}
// Name: SetLength
// Desc - Sets the length of the track
// Preconditions - Requires length
// Postconditions - Sets the length of the track
void Track::SetLength(int length)
{
    m_length = length;
}
// Name: PopulatsObstacles()
// Desc - For each length of track, assigns random type of obstacle (speed, agility, jump)
//        Uses integers (0 = speed, 1 = agility, 2 = jump)
// Preconditions - Track exists
// Postconditions - Populates m_obstacle with random number between 0 and 2
void Track::PopulateObstacles()
{
    //fills m_obstacle array with random number from 0-2
    for (int i = 0; i < m_length; i++)
    {
        m_obstacle[i] = (rand() % 3);
    }
}
// Name: GetStatus()
// Desc - Returns the status of race
// Preconditions - Track exists
// Postconditions - Outputs where each racer is in track and the type of obstacle
void Track::GetStatus()
{
    //iterates over each player in m_track array
    for (int i = 0; i < NUM_RACERS; i++)
    {
        //outputs player's current location in the race and the obstacle type they are on
        if (i == 0)
        {
            cout << "You are on a " << OBSTACLE_TYPE[m_obstacle[m_track[i]]] << " obstacle (obstacle " << m_track[i] + 1 << " of " << m_length << ")" << endl;
        }
        //outputs the computers' current location in the race and the obstacle type they are on
        else
        {
            cout << "Player " << i << " is on a " << OBSTACLE_TYPE[m_obstacle[m_track[i]]] << " obstacle in (obstacle " << m_track[i] + 1 << " of " << m_length << ")" << endl;
        }
    }
}
// Name: CheckWin()
// Desc - Checks to see if the race is over by comparing each racer's
//        location to the length of the track.
//        Returns number of player who wins race (always starts at 0 first)
// Preconditions - Track exists
// Postconditions - Returns integer location of winner (0 is human). Always returns human in case of tie!
int Track::CheckWin()
{
    //iterates over each racer
    for(int i = 0; i < NUM_RACERS; i++)
    {
        //checks to see if their position exceeds the length of the track, the player number is returned if they won
        if ((m_track[i] + 1) > m_length)
        {
            return i;
        }
    }
    //returns -1 if no one has won
    return -1;
}


// Name: GetObstacle
// Desc - Returns the integer of the obstacle at a specific location
// Preconditions - Track exists
// Postconditions - Returns 0 for speed, 1 for agility, and 2 for jump
int Track::GetObstacle(int location)
{
    return m_obstacle[m_track[location]];
}
// Name: IncrementLocation
// Desc - Increments the m_track value for a specific player the human player
//        is always in position 0
// Preconditions - Race starts with everyone having a 0
// Postconditions - Increases the integer value for a specific player
void Track::IncrementLocation(int player)
{
    m_track[player]++;
}
// Name: ResetLocation
// Desc - Before each race, resets the starting location for all players back to 0
// Preconditions - Track exists
// Postconditions - All players has a starting location of 0 in the m_track
void Track::ResetLocation()
{
    //iterates over each player in the m_track array
    for (int i = 0; i < NUM_RACERS; i++)
    {
        //sets their position back to 0
        m_track[i] = 0;
    }
}
// Name: ConvertObstacle
// Desc - Returns the string name of the obstacle using the OBSTACLE_TYPE
//        array for a specific player
// Preconditions - Player exists in m_track
// Postconditions - Pulls the location from m_track for a provided player
//                  then returns the obstacle at that location
string Track::ConvertObstacle(int player)
{
    return OBSTACLE_TYPE[m_obstacle[m_track[player]]];
}

/*
Instance Variables:
int m_track[NUM_RACERS]; //Location of each racer on track
int m_length; //Length of track
int m_obstacle[MAX_LENGTH]; //Type of obstacle in part of track (0=speed, 1=agility, 2=jump)
*/