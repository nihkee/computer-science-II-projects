/*
** File: Race.cpp
** Assignment Name: Project 2 – UMBC Racer
** Author: Nikki Cayas
** Date: 10/6/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Race class
*/
#include "Race.h"

/*
Constants (no additional constants allowed - use local constants if needed):
const int COMP_MAX = 100; //Maximum number for a computer based player (used to randomly choose a number between 40 - 100 to see if succesfully get passed obstacle)
const int COMP_MIN = 40; //Minimum number for computer based player (used to randomly choose a number between 40 - 100 to see if succesfully get passed obstacle)
const int BASE_SKILL = 50; //Player's base chance of getting through obstacle
const int BASE_DIFFICULTY = 100; //Max value of the difficulty of an obstacle. At 100, this would be a random number between 1 and 100.
*/

// Name: Race() Default Constructor
// Desc - Instantiates an object of type Race. Does nothing.
// Preconditions - None
// Postconditions - None
Race::Race()
{

} 

// Name: StartRace()
// 1. Resets length of race
// 2. Increments the number of races for the player
// 3. Sets up track (user chooses length of track) and populates obstacles
// 4. Calls RaceOptions and calls GetStatus or calls ProgressRace (passes the user's choice)
// 5. Checks to see if someone won (their location exceeds the length of the race)
// 6. Displays the winner of race. If human player wins, increases a stat and increases wins 
// Preconditions - Race conditions set up
// Postconditions - Race completed
void Race::StartRace()
{
    //resets length of race
    m_track.SetLength(0);
    //resets all players location back to 0 (beginning)
    m_track.ResetLocation();
    //increments player's total number of races
    m_myPlayer.SetRaces(m_myPlayer.GetRaces() + 1);
    int num = 0;
    cout << "How long would you like the race? " << endl;
    //takes in user input for how many obstacles the race should have
    cin >> num;
    //input validation, length must be between 1 & 100
    while (num > 100 || num < 1)
    {
        cout << "How long would you like the race? " << endl;
        cin >> num;
    }
    //sets the length of the track accordingly
    m_track.SetLength(num);
    //populates track array with obstacles
    m_track.PopulateObstacles();
    int winner = -1;
    //main while loop, program exits loop once someone has won
    while (winner == -1)
    {
        int raceOption = RaceOptions();
        //race status is displayed if user chooses so
        if (raceOption == 1)
        {
            m_track.GetStatus();
        }
        //progressRace is called if user chooses to sprint, dodge, or jump
        else
        {  
            ProgressRace(raceOption - 2);
            //after every progression, program checks for a winner. If there is a winner, the winner is displayed and the while loop is exited
            winner = m_track.CheckWin();
            if (winner == 0)
            {
                cout << "You won the race!" << endl;
                //if user wins, their stats and wins are incremented accordingly
                m_myPlayer.IncreaseStat();
                m_myPlayer.IncreaseWins();
            }
            else if (winner > 0)
            {
                cout << "Player " << winner << " won the race!" << endl;
            }
        }
    }
}
// Name: GetRacerInfo()
// Desc - Gets the racer's name and populates the racer's name
// Preconditions - Populates m_name in Racer
// Postconditions - m_name is populated
void Race::GetRacerInfo()
{
    //takes in user's racer name and stores it
    string racerName;
    cout << "What is your racer's name?" << endl;
    getline(cin, racerName);
    m_myPlayer.SetName(racerName);
}
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
void Race::ProgressRace(int raceOption)
{
    //randomly generates number that represents the obstacle's difficulty (1-100)
    int obstacleDifficulty = (rand() % BASE_DIFFICULTY) + 1;
    cout << "You are trying to progress the race!" << endl;
    //stores player's stat for the current obstacle type they are on
    int stat = m_myPlayer.GetStat(m_track.GetObstacle(0));
    //checks to see if the user's race option matches the obstacle type
    //if it doesnt, then their chance of winning is only equal to the base skill of 50
    if (raceOption != m_track.GetObstacle(0))
    {
        stat = 0;
    }
    //if the user's chance of winning is greater than the obstacle's difficulty level, then their success is displayed and their location gets incremented
    if ((BASE_SKILL + (5 * stat)) > obstacleDifficulty)
    {
        cout << "You made it through the " << m_track.ConvertObstacle(0) << " obstacle!"<< endl;
        m_track.IncrementLocation(0);
    }
    //if the user's chance of winning is less than or equal to the obstacle's difficulty level, then their fall is displayed and the total number of falls is incremented
    else
    {
        cout << "You fell!" << endl;
        m_myPlayer.SetFalls(m_myPlayer.GetFalls() + 1);
    }
    //progression in race for computer players
    ProgressComputer(obstacleDifficulty);
}
// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - None
// Postconditions - Returns number including exit
bool Race::MainMenu()
{
    int choice = 0;
    cout << "What would you like to do?" << endl;
    cout << "1. Start New Race" << endl;
    cout << "2. View Racer History" << endl;
    cout << "3. Quit" << endl;
    //takes in user input for main menu choice
    cin >> choice;
    //input validation, must be between 1-3
    while (choice < 1 || choice > 3)
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Start New Race" << endl;
        cout << "2. View Racer History" << endl;
        cout << "3. Quit" << endl;
        cin >> choice;
    }
    //executes user's main menu choice accordingly (1 starts a race, 2 displays player's status, 3 quits the program)
    switch (choice)
    {
        case 1:
            StartRace();
            break;
        case 2:
            m_myPlayer.DisplayStatus();
            break;
        case 3:
            return true;
    }
    //returns false if the user does not want to quit
    return false;
}
// Name: RaceOptions()
// Desc - Displays the race menu (display status, choose speed, choose agility, or choose jump)
// Preconditions - None
// Postconditions - Returns integer of user choice (status = 1, speed = 2, agility = 3, jump = 4)
int Race::RaceOptions()
{
    int choice = 0;
    cout << "What would you like to do?" << endl;
    cout << "1. Get Race Status" << endl;
    cout << "2. Try to Sprint (Speed)" << endl;
    cout << "3. Try to Dodge (Agility)" << endl;
    cout << "4. Try to Jump (Jump)" << endl;
    //takes in user input for what they want to do in the race
    cin >> choice;
    //input validation, choice must be between 1-4
    while (choice < 1 || choice > 4)
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Get Race Status" << endl;
        cout << "2. Try to Sprint (Speed)" << endl;
        cout << "3. Try to Dodge (Agility)" << endl;
        cout << "4. Try to Jump (Jump)" << endl;
        cin >> choice;
    }
    //returns user's choice
    return choice;
}

// Name: ManageGame
// Desc - Calls RaceTitle, then calls GetRacerInfo. Continually calls MainMenu
//        until the user chooses quit then it thanks the user and quits
// Preconditions - Game instantiated
// Postconditions - Calls RaceTitle, then calls GetRacerInfo. Continually calls MainMenu
//                  until the user chooses quit then it thanks the user and quits
void Race::ManageGame()
{
    //displays race title 
    RaceTitle();
    //retrieves user's racer name
    GetRacerInfo();
    bool quit = MainMenu();
    //main while loop, continuously checks to see if the user wants to quit the program. loops exit if the user wants to quit
    while (quit == false)
    {
        quit = MainMenu();
    }
    cout << "Thanks for playing UMBC Race!" << endl;
}
// Name: ProgressComputer
// Desc - Iterates over each computer player (players 2, 3, and 4) to see if they
//        successfully navigate through an obstacle. Indicates if they make it or fall.
//        Compares a random number between COMP_MIN and COMP_MAX to the obstacle difficulty
//        to see if they are successful
// Preconditions - obstacleDifficulty is already calculated and passed to this function
// Postconditions - For each computer player, they either make it and increment their
//                  location or fall and remain on the same obstacle
void Race::ProgressComputer(int obstacleDifficulty)
{
    //iterates over each computer player
    for (int i = 1; i < NUM_RACERS; i++)
    {
        //generates random number to represent computer's chance of winning (40-100)
        int compSkill = (rand() % (COMP_MAX - COMP_MIN + 1)) + COMP_MIN;
        //if computer's chance of winning is greater than the obstacle's difficulty, then their success is displayed and location is incremented in the m_track array
        if (compSkill > obstacleDifficulty)
        {
            cout << "Player " << i << " made it through the " << m_track.ConvertObstacle(i) << " obstacle!" << endl;
            m_track.IncrementLocation(i);
        }
        //otherwise, nothing gets incremented in the m_track array, and their fall is displayed
        else
        {
            cout << "Player " << i << " fell!" << endl;
        }
    }
}

/*
Instance vars:
Player m_myPlayer; //Player information for game
Track m_track; //Track for race
*/