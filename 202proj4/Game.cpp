/*
** File: Game.cpp
** Assignment Name: Project 4 – UMBC Starcraft
** Author: Nikki Cayas
** Date: 11/16/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Game class
*/

#include "Game.h"

/*
const int MARINE_HEALTH = 8; //starting health for marine
const int GHOST_HEALTH = 10;  //starting health for ghost
const int BATTLECRUISER_HEALTH = 12; //starting health for battlecruiser
const int TERRAN_HEALTH = 10; //starting health for terran
const int ZERGLING_HEALTH = 3; //starting health for zergling
const int MUTALISK_HEALTH = 5; //starting health for mutalisk
const int HYDRALISK_HEALTH = 7; //starting health for hydralisk
const int NUM_RESTS = 1; //starting rests for player
const int NUM_SPECIAL = 3; //starting special attacks for player
const int REST_HEAL = 10; //how much health is restored from rest
const int START_AREA = 0; //starting area number
const int START_WINS = 0; //starting number of wins
const string FILE_NAME = "proj4_map1.txt"; //default for default game constructor
const char DELIMITER = '|'; //delimiter for input file (map file)
*/

// Name: Game() - Default Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including rests, specials, curArea, filename, curZerg (nullptr), and starting wins
Game::Game()
{
    m_myTerran = nullptr;
    m_curArea = START_AREA;
    m_curZerg = nullptr;
    m_numRests = NUM_RESTS;
    m_numSpecial = NUM_SPECIAL;
    m_filename = FILE_NAME;
    m_wins = START_WINS;
}
// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
//                 including rests, specials, curArea, filename (from passed variable),
//                 curZerg (nullptr), and starting wins
Game::Game(string filename)
{
    m_myTerran = nullptr;
    m_curArea = START_AREA;
    m_curZerg = nullptr;
    m_numRests = NUM_RESTS;
    m_numSpecial = NUM_SPECIAL;
    m_filename = filename;
    m_wins = START_WINS;
}
// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated in Game (terran, zergs, and map)
Game::~Game()
{
    //iterates through map vector
    for (unsigned int i = 0; i < m_myMap.size(); i++)
    {
        //deallocates memory at each position in the vector
        delete m_myMap.at(i);
    }
    //clears vector
    m_myMap.clear();
    //deallocates memory for player and zerg pointers
    delete m_myTerran;
    delete m_curZerg;
    //sets pointers equal to nullptr for security
    m_myTerran = nullptr;
    m_curZerg = nullptr;
}
// Name: LoadMap()
// Description: Dynamically creates areas and inserts them into the m_myMap vector
// Note: the size of the map is not known - you should not use constants for this.
//       Also, you can use stoi to convert strings to integers
// Precondition: m_filename is populated
// Postcondition: Map is populated with area objects.
void Game::LoadMap()
{
    //declares strings that store data from text file
    string id, name, desc, north, east, south, west;
    //declares input stream and opens file
    ifstream inputStream(m_filename);
    //checks to see if there is more content in the text file
    while (getline(inputStream, id, DELIMITER))
    {
        //reads in each map's instance variable and stores it in the local vars
        getline(inputStream, name, DELIMITER);
        getline(inputStream, desc, DELIMITER);
        getline(inputStream, north, DELIMITER);
        getline(inputStream, east, DELIMITER);
        getline(inputStream, south, DELIMITER);
        getline(inputStream, west);
        //adds the dynamically allocated area to the map vector
        m_myMap.push_back(new Area(stoi(id), name, desc, stoi(north), stoi(east), stoi(south), stoi(west)));
    }
    //closes file
    inputStream.close();
}
// Name: TerranCreation()
// Description: Allows user to choose a new terran (or child) to play with. May
//              be either Terran, Marine, Ghost, or Battlecruiser.
// Preconditions: None
// Postconditions: m_myTerran is populated
void Game::TerranCreation()
{
    int choice = 0;
    //takes in user input for the player's name
    string name;
    cout << "Terran Name: " << endl;
    getline(cin, name);
    //takes in which terran the user wants to play as, also checks for input validation (1-4)
    do
    {
        cout << "Select a class" << endl;
        cout << "1. Marine" << endl;
        cout << "2. Ghost" << endl;
        cout << "3. Battlecruiser" << endl;
        cout << "4. No Class" << endl;
        cin >> choice;
    }
    while (choice < 1 || choice > 4);
    //dynamically allocates terran based on user's choice
    switch (choice)
    {
        case 1:
            m_myTerran = new Marine(name, MARINE_HEALTH);
            break;
        case 2:
            m_myTerran = new Ghost(name, GHOST_HEALTH);
            break;
        case 3:
            m_myTerran = new Battlecruiser(name, BATTLECRUISER_HEALTH);
            break;
        case 4:
            m_myTerran = new Terran(name, TERRAN_HEALTH);
            break;
    }
}
// Name: StartGame()
// Description: Welcomes the player to the game. Calls LoadMap, TerranCreation,
//              prints the current area then calls action
// Preconditions: Input file must exist
// Postconditions: Map is loaded, User has chosen a terran to play with,
//                 printed the starting area, and calls action
void Game::StartGame()
{
    //displays welcoming message
    cout << "Welcome to UMBC Starcraft!" << endl;
    //populates map vector
    LoadMap();
    //creates a terran to act as user's player
    TerranCreation();
    //prints starting area
    m_myMap.at(m_curArea) -> PrintArea();
    //calls main game menu
    Action();
}
// Name: Action()
// Description: Menu for game. Calls RandomZerg for current location then displays menu.
//              Player can look, move, attack, rest, stats, or quit
//              If player moves, clears out the m_curZerg and sets m_curZerg = RandomZerg
//              If player looks, will NOT display zerg again (as this is a function of moving)
//              Can only attack if there is actually a zerg in this area
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until quit or player dies
void Game::Action()
{
    bool quit = false;
    int choice = 0;
    m_curZerg = RandomZerg();
    //main while loop, controls when game ends
    while (quit == false)
    {
        //displays main menu, checks input validation (1-6)
        do
        {
            cout << "What would you like to do?" << endl;
            cout << "1. Look" << endl;
            cout << "2. Move" << endl;
            cout << "3. Attack Zerg" << endl;
            cout << "4. Rest" << endl;
            cout << "5. Check Stats" << endl;
            cout << "6. Quit" << endl;
            cin >> choice;
        }
        while (choice < 1 || choice > 6);
        //if user chooses to look, details of the current area is printed
        if (choice == 1)
        {
            m_myMap.at(m_curArea) -> PrintArea();
        }
        //if user chooses to move, move() is called, m_curZerg is deallocated, m_curZerg is set to a new random zerg
        else if (choice == 2)
        {
            Move();
            delete m_curZerg;
            m_curZerg = RandomZerg();
        }
        //if user chooses to attack, attack() is called
        else if (choice == 3)
        {
            //attack() is called only if there is a zerg present at the current area
            if (m_curZerg != nullptr)
            {
                Attack();
            }
            else
            {
                cout << "There is no zerg to be attacked." << endl;
            }
        }
        //if user chooses to rest, rest() is called
        else if (choice == 4)
        {
            //rest() is called only if the player has rests left (m_numRests is greater than 0)
            if (m_numRests > 0)
            {
                Rest();
            }
            else
            {
                cout << "You are out of rests!" << endl;
            }
        }
        //if user chooses to check stats, stats() is called
        else if (choice == 5)
        {
            Stats();
        }
        //if user chooses to quit, the main while loop is exited
        else
        {
            quit = true;
        }
        //conditional that constantly checks if the player has died. If they have died, the main while loop is exited and the game is terminated
        if(m_myTerran -> GetHealth() <= 0)
        {
            quit = true;
        }
    }
    //displays good bye message
    cout << "Good bye!" << endl;
}
// Name: RandomZerg()
// Description: Used to randomly create a dynamically allocated zerg
//              (25% chance of nothing, 25% chance of Zergling, Mutalisk, or Hydralisk.)
//              When chosen, displays the description
//              of the zerg or displays "It is peaceful here."
// Preconditions: Has an entity pointer to hold zerg child or nullptr
// Postconditions: Returns object of type Zergling, Mutalisk, Hydralisk, or nullptr
Entity* Game::RandomZerg()
{
    //generates a random number between 0-3
    int random = rand() % 4;
    //represents a 25% chance of no zerg spawning/ m_curZerg being assigned nullptr
    if (random == 0)
    {
        m_curZerg = nullptr;
        cout << "It is peaceful here." << endl;
    }
    //represents a 25% chance of m_curZerg being assigned dynamically allocated zergling
    else if (random == 1)
    {
        m_curZerg = new Zergling("Zergling", ZERGLING_HEALTH);
        cout << "A small terrifying zergling waits here." << endl;
    }
    //represents a 25% chance of m_curZerg being assigned dynamically allocated mutalisk
    else if (random == 2)
    {
        m_curZerg = new Mutalisk("Mutalisk", MUTALISK_HEALTH);
        cout << "A large flying mutalisk hovers here." << endl;
    }
    //represents a 25% chance of m_curZerg being assigned dynamically allocated hydralisk
    else
    {
        m_curZerg = new Hydralisk("Hydralisk", HYDRALISK_HEALTH);
        cout << "A medium sized hydralisk slithers here waiting to cover you with acid." << endl;
    }
    //returns m_curzerg that now has been assigned value based on the randomly generated number
    return m_curZerg;
}
// Name: Rest
// Description: If no zerg in current area, allows player to rest
// Preconditions: Must be valid area with no zerg (area must exist) and have rests
// Postconditions: Reduces available rests by one and increases hp by 10
//                 using REST_HEAL (regardless of starting value)
void Game::Rest()
{
    //if there is no zerg in the current area and the current area exits, player is allowed to rest. m_numRests and health is updated accordingly
    if(m_curZerg == nullptr && m_curArea != -1)
    {
        cout << "You rest and wake up refreshed." << endl;
        m_numRests--;
        m_numSpecial = NUM_SPECIAL;
        m_myTerran -> SetHealth(m_myTerran -> GetHealth() + REST_HEAL);
    }
    //otherwise, user cannot rest. no variables are updated
    else
    {
        cout << "You cannot rest with a zerg in the area." << endl;
    }
}
// Name: Move
// Description: Asks a player which direction they would like to move.
//              Moves player from one area to another (updates m_curArea)
// Preconditions: Must be valid move (area must exist)
// Postconditions: Displays area information
void Game::Move()
{
    char direction;
    int validArea = 0;
    //takes in user input for which direction they want to go
    cout << "Which direction? (N E S W)" << endl;
    cin >> direction;
    validArea = (m_myMap.at(m_curArea)) -> CheckDirection(direction);
    //checks for input validation, chosen direction must be of a valid area
    while(validArea == -1)
    {
        cout << "Which direction? (N E S W)" << endl;
        cin >> direction;
        validArea = (m_myMap.at(m_curArea)) -> CheckDirection(direction);
    }
    //sets m_curArea to the area of the chosen direction
    m_curArea = validArea;
    //prints out the new area's details
    m_myMap.at(m_curArea) -> PrintArea();
}
// Name: Attack
// Description: Allows player to attack an enemy entity.
// Preconditions: Must have enemy Zerg in area
// Postconditions: Indicates who wins and updates health(hp) as battle continues.
//                 Both Terran and Zerg attack every round until one or more has <= 0 health
//                 May need to deallocate enemy Zerg to prevent memory leaks.
//                 When either Zerg or Terran <= 0 health, calls ProcessBattle
void Game::Attack()
{
    int choice = 0;
    int random = 0;
    //while loop that ensures that both zerg and terran keep fighting as long as one of them are alive
    //loop is exited when one of their healths is below or equal to 0
    while (m_curZerg -> GetHealth() > 0 && m_myTerran -> GetHealth() > 0)
    {
        //takes in user input for what kind of attack they want to release, checks for input validation (1-2)
        do
        {
            cout << "1. Normal Attack" << endl;
            cout << "2. Special Attack" << endl;
            cin >> choice;
        }
        while (choice < 1 || choice > 2);
        //if user chooses 1, terran executes normal attack
        if (choice == 1)
        {
            m_curZerg -> SetHealth((m_curZerg -> GetHealth()) - (m_myTerran -> Attack()));
        }
        //if user chooses 2, terran executes special attack, zerg's health is decreased accordingly
        else
        {
            if (m_numSpecial > 0)
            {
                m_curZerg -> SetHealth((m_curZerg -> GetHealth()) - (m_myTerran -> SpecialAttack()));
                m_numSpecial--;
            }
            else
            {
                //takes in user input for what kind of attack they want to release, checks for input validation, user MUST choose to do a regular attack (1)
                do
                {
                    cout << "You're out of special attacks until you rest!" << endl;
                    cout << "1. Normal Attack" << endl;
                    cout << "2. Special Attack" << endl;
                    cin >> choice;
                }
                while (choice != 1);
                //executes a regular attack instead of a special attack because the player ran out of special attacks
                m_curZerg -> SetHealth((m_curZerg -> GetHealth()) - (m_myTerran -> Attack()));
            }
        }
        //generates random number between 0-3
        random = rand() % 4;
        //represents 25% chance of zerg executing special attack, terran's health is decreased accordingly
        if (random == 0)
        {
            m_myTerran -> SetHealth((m_myTerran -> GetHealth()) - (m_curZerg -> SpecialAttack()));   
        }
        //represents 75% chance of zerg executing normal attack, terran's health is decreased accordingly
        else
        {
            m_myTerran -> SetHealth((m_myTerran -> GetHealth()) - (m_curZerg -> Attack()));  
        }
        //outputs player's and zerg's health if they're both still alive
        if (m_curZerg -> GetHealth() > 0 && m_myTerran -> GetHealth() > 0)
        {
            cout << *m_myTerran << endl;
            cout << *m_curZerg << endl;
        }
    }
    //if both zerg's and terran's health are less than or equal to 0 and are equal, it indicates in a mutual destruction. both have died
    if (m_myTerran -> GetHealth() <= 0 && m_curZerg -> GetHealth() <= 0)
    {
        ProcessBattle(false, false);
    }
    //if zerg's health is less than terran's health, it indicates that the player has won (zerg died)
    else if (m_myTerran -> GetHealth() > m_curZerg -> GetHealth())
    {
        ProcessBattle(false, true);
    }
    //if terran's health is less than zerg's health, it indicates that the player has lost (terran died)
    else if (m_myTerran -> GetHealth() < m_curZerg -> GetHealth())
    {
        ProcessBattle(true, false);
    }
}
// Name: Stats()
// Description: Displays the information about the player (name, hp, rests, specials, and wins)
// Preconditions: None
// Postconditions: None
void Game::Stats()
{
    //displays player's current stats using getters
    cout << "Name: " << m_myTerran -> GetName() << endl;
    cout << "HP: " << m_myTerran -> GetHealth() << endl;
    cout << "Rests: " << m_numRests << endl;
    cout << "Special: " << m_numSpecial << endl;
    cout << "Wins: " << m_wins << endl;
}
// Name: ProcessBattle
// Description: Called when either the zerg or terran have no health left
//       Displays who won (Zerg, Terran, mutual destruction), adds wins if necessary,
//       and has a 10% chance of earning another rest action.
// Preconditions: Zerg or terran are <= 0 health
// Postconditions: 
void Game::ProcessBattle(bool zergAlive, bool alive)
{
    //generates a random number between 0-9
    int random = rand() % 10;
    //if the player is still alive, the player has won
    if (alive)
    {
        //m_wins incremented, win is displayed
        cout << "You have defeated the " << m_curZerg -> GetName() << "." << endl;        
        m_wins++;
        //represents 10% chance of the player getting another rest action
        if (random == 0)
        {
            cout << "You have earned another rest action!" << endl;
            m_numRests++;
        }
        //deallocates zerg pointer because it is defeated
        delete m_curZerg;
        m_curZerg = nullptr;
    }
    //if zerg is alive, player has lost
    else if(zergAlive)
    {
        //lost is displayed
        cout << "You were defeated by the " << m_curZerg -> GetName() << endl;
        cout << "Please play again!" << endl;
    }
    //if both are dead, results in mutal destructual
    else
    {
        //lost is displayed
        cout << "You defeated each other at the same time!" << endl;
        cout << "Please play again!" << endl;
    }
}

/*
private instance vars:
vector<Area*> m_myMap; // Vector for holding all areas in game
Entity* m_myTerran; // Entity pointer for Terran (Marine, Ghost, or Battlecruiser) - Player
int m_curArea; // Current area that player (Terran) is in
Entity* m_curZerg; // Current zerg loaded for current area
int m_numRests; // Number of rests for player (Terran)
int m_numSpecial; // Number of special attacks for player (Terran) (refreshed after rests)
string m_filename; //Name of the input file for the map (holds area objects)
int m_wins; //Number of battles won in this game
*/