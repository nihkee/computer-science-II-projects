//Title: Race.h
//Author: Jeremy Dixon
//Date: 2/29/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC

#ifndef RACE_H //Header Guard
#define RACE_H //Header Guard
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Player.h" //User defined class required by Race
#include "Track.h" //User defined class required by Race

//Constants (no additional constants allowed - use local constants if needed)
const int COMP_MAX = 100; //Maximum number for a computer based player (used to randomly choose a number between 40 - 100 to see if succesfully get passed obstacle)
const int COMP_MIN = 40; //Minimum number for computer based player (used to randomly choose a number between 40 - 100 to see if succesfully get passed obstacle)
const int BASE_SKILL = 50; //Player's base chance of getting through obstacle
const int BASE_DIFFICULTY = 100; //Max value of the difficulty of an obstacle. At 100, this would be a random number between 1 and 100.

//No additional functions allowed

class Race{
public:
  // Name: Race() Default Constructor
  // Desc - Instantiates an object of type Race. Does nothing.
  // Preconditions - None
  // Postconditions - None
  Race(); //Default Constructor
  // Name: StartRace()
  // 1. Resets length of race
  // 2. Increments the number of races for the player
  // 3. Sets up track (user chooses length of track) and populates obstacles
  // 4. Calls RaceOptions and calls GetStatus or calls ProgressRace (passes the user's choice)
  // 5. Checks to see if someone won (their location exceeds the length of the race)
  // 6. Displays the winner of race. If human player wins, increases a stat and increases wins 
  // Preconditions - Race conditions set up
  // Postconditions - Race completed
  void StartRace();
  // Name: GetRacerInfo()
  // Desc - Gets the racer's name and populates the racer's name
  // Preconditions - Populates m_name in Racer
  // Postconditions - m_name is populated
  void GetRacerInfo();
  // Name: ProgressRace()
  // Desc - Does the following:
  // 1. Deals with the human player first.
  // 2. Randomly assigns (1 - 100) difficlty to all obstacles (regardless of location,
  //    all players have the same level difficulty for each round)
  // 3. Compares the BASE_SKILL + (5 * stat) to the obstacle difficulty to see if successfully
  //    navigated. Indicates if successful and increments location. If not successful,
  //    falls and increments falls
  // 4. Calls ProgressComputer to deal with computer
  // Preconditions - Player in race
  // Postconditions - Each racer either progresses to the next obstacle, or falls
  void ProgressRace(int);
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - None
  // Postconditions - Returns number including exit
  bool MainMenu();
  // Name: RaceOptions()
  // Desc - Displays the race menu (display status, choose speed, choose agility, or choose jump)
  // Preconditions - None
  // Postconditions - Returns integer of user choice (status = 1, speed = 2, agility = 3, jump = 4)
  int RaceOptions();
  // Name: ManageGame
  // Desc - Calls RaceTitle, then calls GetRacerInfo. Continually calls MainMenu
  //        until the user chooses quit then it thanks the user and quits
  // Preconditions - Game instantiated
  // Postconditions - Calls RaceTitle, then calls GetRacerInfo. Continually calls MainMenu
  //                  until the user chooses quit then it thanks the user and quits
  void ManageGame();
  // Name: ProgressComputer
  // Desc - Iterates over each computer player (players 2, 3, and 4) to see if they
  //        successfully navigate through an obstacle. Indicates if they make it or fall.
  //        Compares a random number between COMP_MIN and COMP_MAX to the obstacle difficulty
  //        to see if they are successful
  // Preconditions - obstacleDifficulty is already calculated and passed to this function
  // Postconditions - For each computer player, they either make it and increment their
  //                  location or fall and remain on the same obstacle
  void ProgressComputer(int obstacleDifficulty);
  // Name: RaceTitle()
  // Desc - Title for Race (Do not edit)
  // Preconditions - None
  // Postconditions - None
  void RaceTitle(){
    cout << "*****************************************************************" << endl;
    cout << "U   U   M   M   BBB   CCCC   RRR     AA    CCCC   EEEE   RRR     " << endl;
    cout << "U   U   MM MM   B  B  C      R  R   A  A   C      E      R  R    " << endl;
    cout << "U   U   M M M   BBBB  C      RRR    AAAA   C      EEEE   RRR     " << endl;
    cout << "U   U   M   M   B  B  C      R R    A  A   C      E      R R     " << endl;
    cout << "UUUUU   M   M   BBB   CCCC   R  R   A  A   CCCC   EEEE   R  R    " << endl;
    cout << "*****************************************************************" << endl;
  }
private:
  Player m_myPlayer; //Player information for game
  Track m_track; //Track for race
};

#endif //Exit Header Guard
