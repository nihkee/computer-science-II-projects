/*
** File: Player.cpp
** Assignment Name: Project 2 – UMBC Racer
** Author: Nikki Cayas
** Date: 10/6/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Player class
*/
#include "Player.h"

/*
Constants:
const int MAX_STAT = 10; //Maximum of any player stat
const int START_STAT = 1; //Starting value of all stats
const int NUM_STATS = 3; //Number of stats for game (speed, agility, jump)
*/

// Name: Player() - Default Constructor
// Desc: Used to build a new Player
// Preconditions - Requires default values
// Postconditions - Creates new Player (with default name of "Beannie" with 1 speed/agility/jump
Player::Player()
{
    m_name = "Beanie";
    //iterates over the m_stat array to initialize its elements to default value of 1
    for (int i = 0; i < NUM_STATS; i++)
    {
        m_stat[i] = START_STAT;
    }
}
// Name: Player(name) - Overloaded constructor
// Desc - Used to build a new Player
// Preconditions - Requires name
// Postconditions - Creates a new Player (with passed name and 1 speed/agility/jump)
// May not be used in the project explicitly but please implement
Player::Player(string name)
{
    m_name = name;
    //iterates over the m_stat array to initialize its elements to default value of 1
    for (int i = 0; i < NUM_STATS; i++)
    {
        m_stat[i] = START_STAT;
    }
}
// Name: GetName()
// Desc - Getter for Player name
// Preconditions - Player exists
// Postconditions - Returns the name of the Player
string Player::GetName()
{
    return m_name;
}
// Name: SetName(string)
// Desc - Allows the user to change the name of the Player
// Preconditions - Player exists
// Postconditions - Sets name of Player
void Player::SetName(string name)
{
    m_name = name;
}
// Name: GetSpeed
// Desc - Gets the speed from this player
// Preconditions - Player has a speed assigned
// Postconditions - Returns the speed of the player
int Player::GetSpeed()
{
    return m_stat[0];
}
// Name: GetAgility
// Desc - Gets the agility from this player
// Preconditions - Player has a agility assigned
// Postconditions - Returns the agility of the player
int Player::GetAgility()
{
    return m_stat[1];
}
// Name: GetJump
// Desc - Gets the jump from this player
// Preconditions - Player has a jump assigned
// Postconditions - Returns the jump of the player
int Player::GetJump()
{
    return m_stat[2];
}
// Name: GetRaces
// Desc - Gets the total number of races the player has run
// Preconditions - Player has a races assigned
// Postconditions - Returns the total number of races run
int Player::GetRaces()
{
    return m_races;
}
// Name: GetFalls
// Desc - Gets the total number of falls for the player
// Preconditions - None
// Postconditions - Returns the total falls for the player
int Player::GetFalls()
{
    return m_falls;
}
// Name: SetRaces
// Desc - Sets the total number of races the player has run
// Preconditions - None
// Postconditions - Sets total number of races run
void Player::SetRaces(int races)
{
    m_races = races;
}
// Name: SetFalls
// Desc - Sets the total number of falls for the player
// Preconditions - None
// Postconditions - Sets the total falls for the player
void Player::SetFalls(int falls)
{
    m_falls = falls;
}
// Name: DisplayStatus
// Desc - Displays the player names and their stats
// Precondition - None
// Postconditions - Displays the player information
void Player::DisplayStatus()
{
    cout << "******* The Mighty Racer " << m_name << " *******" << endl;
    cout << "Races: " << m_races << endl;
    cout << "Wins: " << m_wins << endl;
    cout << "Falls: " << m_falls << endl;
    cout << "\nStats" << endl;
    cout << "Speed: " << m_stat[0] << endl;
    cout << "Agility: " << m_stat[1] << endl;
    cout << "Jump: " << m_stat[2] << endl;
}
// Name: IncreaseStat
// Desc - Asks the user for a stat to increase (speed, agility, or jump) up to a max of 10
// Precondition - Called after winning a race
// Postconditions - Increases one stat by one point (max 10)
void Player::IncreaseStat()
{
    int chosenStat = 0;
    cout << "Which stat would you like to increase?" << endl;
    cout << "1. Speed" << endl;
    cout << "2. Agility" << endl;
    cout << "3. Jump" << endl;
    //takes in user input to see what stat they would like to increment
    cin >> chosenStat;
    //checks for input validation (must be between 1 & 3)
    while ((chosenStat > 3) || (chosenStat < 1))
    {
        cout << "Which stat would you like to increase?" << endl;
        cout << "1. Speed" << endl;
        cout << "2. Agility" << endl;
        cout << "3. Jump" << endl;
        cin >> chosenStat;
    }
    //increments stat based on user input
    switch(chosenStat)
    {
        case 1:
            m_stat[0]++;
            break;
        case 2:
            m_stat[1]++;
            break;
        case 3:
            m_stat[2]++;
            break;
    }
}
// Name: GetStat
// Desc - Returns the value of a stat at a specific location (0 = speed, 1 = agility, 2 = jump)
// Precondition - None
// Postconditions - Returns the integer value of a specific stat
int Player::GetStat(int stat)
{
    return m_stat[stat];
}
// Name: IncreaseWins
// Desc - Increases the number of wins by 1
// Precondition - None
// Postconditions - Increases the number of wins by 1
void Player::IncreaseWins()
{
    m_wins++;
}

/*
Instance Variables:
string m_name; //Name of Player
int m_stat[3]; //Stats of player: 0 = speed, 1 = agility, 2 = jump
int m_races; //Starts at 0
int m_wins; //Starts at 0
int m_falls; //Starts at 0
*/