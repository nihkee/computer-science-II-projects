//Title: MusicPlayer.h
//Author: Jeremy Dixon
//Date: 10/5/2022
//Description: This is part of the project 3 in CMSC 202 @ UMBC
//This is the music player that holds a music catalog and allows the user to build a playlist
//Do not edit this header file

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Song.h"
#include "Playlist.h"

using namespace std;

//Constants
const int LOW_YEAR = 2010; //First year of music catalog
const int HIGH_YEAR = 2021; //Last year of music catalog
const string FILE_NAME = "proj3_music.txt"; //Default input file
const char DELIMITER = '|'; //Default delimiter for the input file

class MusicPlayer{
 public:
  //Name: MusicPlayer - Default Constructor ******
  //Precondition: None
  //Postcondition: Dynamically allocates a vector to hold playlist objects
  MusicPlayer();
  //Name: ~MusicPlayer - Destructor ******
  //Precondition: None
  //Postcondition: Destructs all songs in the catalog and all songs in each playlist
  ~MusicPlayer();
  //Name: LoadCatalog(string filename)
  //Precondition: Requires filename
  //Postcondition: Loads the file of songs into the m_songCatalog (as song objects) using the DELIMITER
  void LoadCatalog(string filename);
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the application and the menu. Calls until user chooses to quit.
  void MainMenu();
  //Name: DisplaySongs
  //Precondition: User enters year using constants above (2010-2021)
  //Postcondition: Lists all songs (numbered) for that year by ranking
  void DisplaySongs();
  //Name: AddSong
  //Precondition: m_songCatalog is populated and m_playList exists
  //Postcondition: Displays the songs for a specific year. Adds a song to the m_playList by dynamically allocating a new song based on the song in the catalog
  //               and inserting it in the end.
  //               May have duplicate songs on a playlist.
  //               If the user chooses 2010, the user does not have to choose something from 2010 but it does need to be valid (between 1 - 1200)
  void AddSong();
  //Name: DisplayPlaylist
  //Precondition: None (can be empty)
  //Postcondition: Displays the playlist or tells the user it is empty
  void DisplayPlaylist();
  //Name: PlaySong
  //Precondition: Playlist should be populated
  //Postcondition: Allows the user to choose a song from the playlist to play.
  //               Removes chosen song from playlist after "played"
  void PlaySong();
  //Name: CreateNewPlaylist
  //Precondition: m_playlistCatalog is declared
  //Postcondition: Allows the user to dynamically create and name a new playlist object
  //               New playlist is added to the m_playlistCatalog vector
  void CreateNewPlaylist();
  //Name: ChoosePlaylist
  //Precondition: m_playlistCatalog should be populated
  //Postcondition: Allows the user to choose which playlist they would like to edit edit/display/play from
  //               Sets m_playlist equal to the playlist chosen by the user, keeping track of the "current" playlist
  void ChoosePlaylist();
  //Name: IsPlaylistSelected
  //Precondition: m_playList should either be pointing to a playlist or should be pointing to nullptr
  //Postcondition: returns bool based on whether or not the user has chosen a playlist to act as the "current" playlist
  bool IsPlaylistSelected();
 private:
  vector<Song*> m_songCatalog; //Holds all songs in input file as songs
  vector<Playlist*> m_playlistCatalog; //Holds all playlists created by user
  Playlist* m_playList; //Holds all songs in the current playlist
};

#endif
