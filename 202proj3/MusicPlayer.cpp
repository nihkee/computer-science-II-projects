/*
** File: MusicPlayer.cpp
** Assignment Name: Project 3 – UMBC Music Player
** Author: Nikki Cayas
** Date: 11/1/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Music Player class
*/
#include "MusicPlayer.h"

/*
Constants:
const int LOW_YEAR = 2010; //First year of music catalog
const int HIGH_YEAR = 2021; //Last year of music catalog
const string FILE_NAME = "proj3_music.txt"; //Default input file
const char DELIMITER = '|'; //Default delimiter for the input file
*/

//Name: MusicPlayer - Default Constructor
//Precondition: None
//Postcondition: Dynamically creates a new MusicPlayer and populates m_filename FILE_NAME
MusicPlayer::MusicPlayer()
{
    m_playList = new Playlist();
}
//Name: ~MusicPlayer - Destructor
//Precondition: None
//Postcondition: Destructs all songs in the catalog and all songs in the playlist
MusicPlayer::~MusicPlayer()
{
    //iterates through entire m_songCatalog vector
    for (unsigned int i = 0; i < m_songCatalog.size(); i++)
    {
        //deletes each song pointer in the vector
        delete m_songCatalog.at(i);
    }
    //clears the m_songCatalog vector
    m_songCatalog.clear();
    //m_playlist linked list is deallocated (implicitly calls destructor)
    delete m_playList;
}
//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file of songs into the m_songCatalog (as song objects) using the DELIMITER
void MusicPlayer::LoadCatalog(string filename)
{
    //declares strings that store data from text file
    string title, artist, year, rank;

    //declares input stream and opens file
    ifstream inputStream(filename);

    //checks to see if there is more content in the text file
    while (getline(inputStream, title, DELIMITER))
    {
        //reads in each song's instance variable and stores it in the local vars
        getline(inputStream, artist, DELIMITER);
        getline(inputStream, year, DELIMITER);
        getline(inputStream, rank);
        //adds the dynamically allocated song to the song catalog
        m_songCatalog.push_back(new Song(title, artist, stoi(year), stoi(rank)));
    }
    //closes file and displays total number of songs loaded
    inputStream.close();
    cout << "Songs loaded: " << m_songCatalog.size() << endl;
}
//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu. Calls until user chooses to quit.
void MusicPlayer::MainMenu()
{
    int menuChoice = 0;
    //main do while loop, keeps running the program until user quits the program by inputting "5"
    do
    {
        //displays menu
        cout << "What would you like to do?" << endl;
        cout << "1. Display Songs by Year" << endl;
        cout << "2. Add Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Play Song" << endl;
        cout << "5. Quit" << endl;
        cin >> menuChoice;
        //checks for input validation, menuChoice must be between 1-5
        while (menuChoice < 1 || menuChoice > 5)
        {
        cout << "What would you like to do?" << endl;
        cout << "1. Display Songs by Year" << endl;
        cout << "2. Add Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Play Song" << endl;
        cout << "5. Quit" << endl;
        cin >> menuChoice;
        }
        //executes user choice based on their input
        switch (menuChoice)
        {
            case 1:
                DisplaySongs();
                break;
            case 2:
                AddSong();
                break;
            case 3:
                DisplayPlaylist();
                break;
            case 4:
                PlaySong();
                break;
        }
    }
    while(menuChoice != 5);
    //program exits when user inputs "5", thank you message is displayed
    cout << "Thank you for using the UMBC Music Player" << endl;
}
//Name: DisplaySongs
//Precondition: User enters year using constants above (2010-2021)
//Postcondition: Lists all songs (numbered) for that year by ranking
void MusicPlayer::DisplaySongs()
{
    //takes in user input for which year they would like to display the songs for
    int year = 0;
    cout << "Which year would you like to display? (2010-2021)" << endl;
    cin >> year;
    //checks for input validation, user's input must be between 2010 - 2021
    while (year > HIGH_YEAR || year < LOW_YEAR)
    {
        cout << "Which year would you like to display? (2010-2021)" << endl;
        cin >> year;
    }
    cout << "******" << year << "*****" << endl;
    //iterates through the entre m_songCatalog vector
    for (unsigned int i = 0; i < m_songCatalog.size(); i++)
    {
        //if the song's year matches the user's chosen year, then the title, artist, year, and rank of the song are displayed in order
        if (m_songCatalog.at(i) -> GetYear() == year)
        {
            cout << i + 1 << ". \"" << m_songCatalog.at(i) -> GetTitle() << "\" by " << m_songCatalog.at(i) -> GetArtist() << " " << m_songCatalog.at(i) -> GetRank() << "/100 from " << m_songCatalog.at(i) -> GetYear() << endl;
        }
    }
}
//Name: AddSong
//Precondition: m_songCatalog is populated and m_playList exists
//Postcondition: Displays the songs for a specific year. Adds a song to the m_playList by dynamically allocating a new song based on the song in the catalog
//               and inserting it in the end.
//               May have duplicate songs on a playlist.
//               If the user chooses 2010, the user does not have to choose something from 2010 but it does need to be valid (between 1 - 1200)
void MusicPlayer::AddSong()
{
    //if playlist is empty, it will be displayed as empty
    if(m_playList -> Size() == 0)
    {
        cout << "***Current Playlist is Empty***" << endl;
    }
    cout << "Choose the songs you would like to add to the playlist." << endl;
    //calls display songs so user can see what songs they want to choose from
    DisplaySongs();
    //takes in user's input for which song from the catalog they want to add to the playlist
    int songNum = 0;
    cout << "Enter the number of the song you would like to add:" << endl;
    cin >> songNum;
    //input validation, user's choice must be in range (1-1200)
    while (songNum < 1 || songNum > (int)m_songCatalog.size())
    {
        cout << "Enter the number of the song you would like to add:" << endl;
        cin >> songNum;
    }
    //declares local variables that stores the title, artist, year, and rank of the selected song
    string title;
    string artist;
    int year = 0;
    int rank = 0;
    //iterates through the entire m_songCatalog
    for (unsigned int i = 0; i < m_songCatalog.size(); i++)
    {
        //checks to see if the selected song number is reached
        if ((int)i == songNum - 1)
        {
            //each element in the vector (song pointer) is derefenced to call the getter methods which returns the title, artist, year, and rank for the selected song
            //the information is stored in the local variables that were created outside of the floor loop
            title = m_songCatalog.at(i) -> GetTitle();
            artist = m_songCatalog.at(i) -> GetArtist();
            year = m_songCatalog.at(i) -> GetYear();
            rank = m_songCatalog.at(i) -> GetRank();
        }
    }
    //the selected song is then added to the playlist linked list using the local variables
    m_playList -> AddSong(title, artist, year, rank);
    //displays which song is added to the playlist linked list
    cout << "Added: \"" << title << "\" by " << artist << " " << rank << "/100 from " << year << endl;
}
//Name: DisplayPlaylist
//Precondition: None (can be empty)
//Postcondition: Displays the playlist or tells the user it is empty
void MusicPlayer::DisplayPlaylist()
{
    //if playlist is empty, its empty state will be displayed
    if (m_playList -> Size() == 0)
    {
        cout << "The playlist is currently empty." << endl;
    }
    //if playlist isnt empty, its contents are displayed
    else
    {
        cout << "Your Playlist" << endl;
        //iterates through the linked list
        for (int i = 0; i < m_playList -> Size(); i++)
        {
            //pointer for each song is dereferenced to call the respective getter methods so the artist, title, year, rank of the song can be displayed
            Song* currSong = m_playList -> GetPlaylistDetails(i);
            cout << i + 1 << ". \"" << currSong -> GetTitle() << "\" by " << currSong -> GetArtist() << " " << currSong -> GetRank() << "/100 from " << currSong -> GetYear() << endl;
        }
    }
}
//Name: PlaySong
//Precondition: Playlist should be populated
//Postcondition: Allows the user to choose a song from the playlist to play.
//               Removes chosen song from playlist after "played"
void MusicPlayer::PlaySong()
{
    //displays playlist at its current state (can be empty or populated)
    DisplayPlaylist();
    //if playlist is not empty, the user can choose what song they'd like to "play" or remove from the playlist
    if(m_playList -> Size() != 0)
    {
        //takes in user input for what song they want to "play" from the playlist
        int songNum = 0;
        cout << "Which song would you like to play? " << endl;
        cin >> songNum;
        //input validation, user's song choice must be in range with the size of playlist
        while (songNum < 1 || songNum > m_playList -> Size())
        {
            cout << "Which song would you like to play? " << endl;
            cin >> songNum;
        }
        //information for the song is displayed, lets user know that their song was "played"
        Song* currSong = m_playList -> GetPlaylistDetails(songNum - 1);
        cout << "Played: \"" << currSong -> GetTitle() << "\" by " << currSong -> GetArtist() << " " << currSong -> GetRank() << "/100 from " << currSong -> GetYear() << endl;
        //song is removed from the playlist linked list using the PlayAt function
        m_playList -> PlayAt(songNum - 1);
    }
}

/*
private instance variables:
vector<Song*> m_songCatalog; //Holds all songs in input file as songs
//vector that holds Songs
Playlist* m_playList; //Holds all songs in play list
*/