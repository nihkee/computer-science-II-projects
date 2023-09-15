/*
** File: MusicPlayer.cpp
** Assignment Name: Project 3 – UMBC Music Player (extra credit)
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
//Postcondition: Initializes m_playlist pointer to nullptr
MusicPlayer::MusicPlayer()
{
    m_playList = nullptr;
}
//Name: ~MusicPlayer - Destructor
//Precondition: None
//Postcondition: Destructs all songs in song catalog and all playlists in playlist catalog
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
    //iterates through entire m_playlistCatalog vector
    for (unsigned int i = 0; i < m_playlistCatalog.size(); i++)
    {
        //deletes each playlist pointer in the vector
        delete m_playlistCatalog.at(i);
    }
    //clears the m_playlistCatalog vector
    m_playlistCatalog.clear();
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
        //reads in each song instance variable;
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
    //main do while loop, keeps running the program until user quits the program by inputting "7"
    do
    {
        //displays menu
        cout << "What would you like to do?" << endl;
        cout << "1. Create New Playlist" << endl;
        cout << "2. Choose Playlist to Edit/Display/Play" << endl;
        cout << "3. Display Songs by Year" << endl;
        cout << "4. Add Song to Current Playlist" << endl;
        cout << "5. Display Current Playlist" << endl;
        cout << "6. Play Song" << endl;
        cout << "7. Quit" << endl;
        cin >> menuChoice;
        //checks for input validation, menuChoice must be between 1-7
        while (menuChoice < 1 || menuChoice > 7)
        {
        cout << "What would you like to do?" << endl;
        cout << "1. Create New Playlist" << endl;
        cout << "2. Choose Playlist to Edit/Display/Play" << endl;
        cout << "3. Display Songs by Year" << endl;
        cout << "4. Add Song to Current Playlist" << endl;
        cout << "5. Display Current Playlist" << endl;
        cout << "6. Play Song" << endl;
        cout << "7. Quit" << endl;
        cin >> menuChoice;
        }
        //executes user choice based on their input
        switch (menuChoice)
        {
            case 1:
                CreateNewPlaylist();
                break;
            case 2:
                ChoosePlaylist();
                break;
            case 3:
                DisplaySongs();
                break;
            case 4:
                //checks to see if user has chosen a "current" playlist before executing the AddSong() function
                if (IsPlaylistSelected())
                {
                    AddSong();
                }
                break;
            case 5:
                //checks to see if user has chosen a "current" playlist before executing the DisplayPlaylist() function
                if (IsPlaylistSelected())
                {
                    DisplayPlaylist();
                }
                break;
            case 6:
                //checks to see if user has chosen a "current" playlist before executing the PlaySong() function
                if (IsPlaylistSelected())
                {
                    PlaySong();
                }
                break;
        }
    }
    while(menuChoice != 7);
    //program exits when user inputs "7", thank you message is displayed
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
        cout << "***Current Playlist (" << m_playList -> GetPlaylistName() << ") is Empty***" << endl;
    }
    cout << "Choose the songs you would like to add to the current playlist (" << m_playList -> GetPlaylistName() << ")." << endl;
    //calls display songs so user can see what songs they want to choose from
    DisplaySongs();
    //takes in user's input for which song from the catalog they want to add to the playlist
    int songNum = 0;
    cout << "Enter the number of the song you would like to add to your current playlist (" << m_playList -> GetPlaylistName() << "):" <<  endl;
    cin >> songNum;
    //input validation, user's choice must be in range (1-1200)
    while (songNum < 1 || songNum > (int)m_songCatalog.size())
    {
        cout << "Enter the number of the song you would like to add to your current playlist (" << m_playList -> GetPlaylistName() << "):" <<  endl;
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
        cout << "The playlist (" << m_playList -> GetPlaylistName() << ") is currently empty." << endl;
    }
    //if playlist isnt empty, its contents are displayed
    else
    {
        cout << "Your Playlist (" << m_playList -> GetPlaylistName() << "):" << endl;
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
    //if playlist is not empty, the user can choose what song they'd like to "play" from the playlist
    if(m_playList -> Size() != 0)
    {
        //takes in user input for what song they want to "play" from the playlist
        int songNum = 0;
        cout << "Which song would you like to play from your current playlist? (" << m_playList -> GetPlaylistName() << ")" << endl;
        cin >> songNum;
        //input validation, user's song choice must be in range (1 - size of playlist)
        while (songNum < 1 || songNum > m_playList -> Size())
        {
            cout << "Which song would you like to play from your current playlist? (" << m_playList -> GetPlaylistName() << ")" << endl;
            cin >> songNum;
        }
        //information for the song is displayed, lets user know that their song was "played"
        Song* currSong = m_playList -> GetPlaylistDetails(songNum - 1);
        cout << "Played: \"" << currSong -> GetTitle() << "\" by " << currSong -> GetArtist() << " " << currSong -> GetRank() << "/100 from " << currSong -> GetYear() << endl;
        //song is removed from the playlist linked list using the PlayAt function
        m_playList -> PlayAt(songNum - 1);
    }
}
//Name: CreateNewPlaylist 
//Precondition: m_playlistCatalog is declared
//Postcondition: Allows the user to dynamically create and name a new playlist object
//               New playlist is added to the m_playlistCatalog vector
void MusicPlayer::CreateNewPlaylist()
{
    //takes in user input that is to be used to set the playlist's name
    string name;
    cout << "What would you like to name your new playlist?" << endl;
    //checks buffer
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }
    getline(cin, name);
    //new playlist obj is dynamically allocated and added to the m_playlistCatalog vector
    Playlist* m_newPlaylist = new Playlist();
    m_newPlaylist -> SetPlaylistName(name);
    m_playlistCatalog.push_back(m_newPlaylist);
    //action is displayed
    cout << name << " playlist was created." << endl;
}
//Name: ChoosePlaylist 
//Precondition: m_playlistCatalog should be populated
//Postcondition: Allows the user to choose which playlist they would like to edit/display/play from
//               Sets m_playlist equal to the playlist chosen by the user, keeping track of the "current" playlist
void MusicPlayer::ChoosePlaylist()
{
    //if the playlist catalog vector size is 0, there are no playlists to be chosen
    if ((int)m_playlistCatalog.size() == 0)
    {
        cout << "You have not created any playlists yet." << endl;
    }
    //if the vector size is not 0, there are playlists to be chosen from
    else
    {
        cout << "Your playlists:" << endl;
        //displays the names of all the playlists
        for (int i = 0; i < (int)m_playlistCatalog.size(); i++)
        {
            cout << i + 1 << ". " << m_playlistCatalog.at(i) -> GetPlaylistName() << endl;
        }
        //takes in user input for which playlist they choose to make the "current" playlist that they can edit, display, and play songs from
        int playlistChoice = 0;
        cout << "Which playlist would you like to edit/display/play?" << endl;
        cin >> playlistChoice;
        //checks input validation, playlistChoice must be between 1 and the total number of playlists
        while (playlistChoice < 1 || playlistChoice > (int)m_playlistCatalog.size())
        {
            cout << "Which playlist would you like to edit/display/play?" << endl;
            cin >> playlistChoice;
        }
        //iterates through the m_playlistCatalog vector
        for (int i = 0; i < (int)m_playlistCatalog.size(); i++)
        {
            //once the number of the chosen playlist is reached, the value for the pointer m_playList is updated to the new "current" playlist
            if (playlistChoice == i + 1)
            {
                m_playList = m_playlistCatalog.at(i);
            }
        }
    }
}
//Name: IsPlaylistSelected
//Precondition: m_playList should either be pointing to a playlist or should be pointing to nullptr
//Postcondition: returns bool based on whether or not the user has chosen a playlist to act as the "current" playlist
bool MusicPlayer::IsPlaylistSelected()
{
    //returns true if m_playList is not pointing to nullptr, false otherwise
    if (m_playList == nullptr)
    {
        cout << "You did not choose a playlist to display yet!" << endl;
        return false;
    }
    return true;
}
/*
private instance variables:
vector<Song*> m_songCatalog; //Holds all songs in input file as songs
vector<Playlist*> m_playlistCatalog; //Holds all playlists created by user
Playlist* m_playList; //Playlist pointer, points towards the "current" playlist
*/