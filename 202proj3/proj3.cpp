//Title: proj3.cpp
//Author: Jeremy Dixon
//Date: 10/5/2022
//Description: This is part of the project 3 in CMSC 202 @ UMBC
//This is the music player that holds a music catalog and allows the user to build a playlist
//Do not edit this file

#include <iostream>
#include "MusicPlayer.h" //Loads the MusicPlayer
#include "Playlist.h" //Loads the Playlist
#include "Song.h" //Loads the Songs

//Takes in an argument when you call this program
//For example, if you type ./proj3 proj3_music.txt it will automatically pass proj3_music.txt in
//as argv[1]. So it is required.
int main (int argc, char* argv[]) {
  string musicFile;
  cout << "Welcome to UMBC Music Player"<<endl;
  if(argc > 1)
  {
    musicFile = argv[1]; //stores the first argument as musicFile
  } 
  else
  {
    cout << "One music files required - try again" << endl;
    cout << "./proj3 proj3_music.txt" << endl;
    return 0;
  }
  MusicPlayer* myMusic = new MusicPlayer(); //Dynamically allocates a new music player
  myMusic->LoadCatalog(musicFile); //Loads the catalog
  myMusic->MainMenu(); //Calls MainMenu
  delete myMusic; //Deallocates the music player
  return 0;
}
