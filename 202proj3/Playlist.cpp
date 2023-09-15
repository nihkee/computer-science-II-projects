/*
** File: Playlist.cpp
** Assignment Name: Project 3 – UMBC Music Player
** Author: Nikki Cayas
** Date: 11/1/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Playlist class
*/
#include "Playlist.h"

// Name: Playlist() - Default Constructor
// Desc - Creates a new empty playlist
// Preconditions - None
// Postconditions - Sets everything to either nullptr or 0
Playlist::Playlist()
{
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}
// Name: ~Playlist - Destructor
// Desc - Removes all of the songs from the playlist
// Preconditions - Playlist must have songs
// Postconditions - Playlist will be empty and m_head and m_tail will be nullptr. Size will be 0
Playlist::~Playlist()
{
    //creates pointer to traverse thru linked list
    Song* curr = m_head;
    //iterates thru linked list
    while (curr != nullptr)
    {
        //curr pointer points to next node & then previous node is deallocated
        m_head = curr;
        curr = curr -> GetNext();
        delete m_head;
    }
    //static linked list values are set back to their default values of nullptr or 0
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
 }
// Name: AddSong(string, string, int, int)
// Desc - Dynamically allocates new song using title, artist, year, and rank
// Preconditions - Playlist allocated
// Postconditions - New song inserted in end of list
void Playlist::AddSong(string title, string artist, int year, int rank)
{
    //allocates new song node
    Song* newSong = new Song(title, artist, year, rank);
    //special case: if list is empty, then the new node is the first node & m_head must point towards this node
    if (m_size == 0)
    {
        m_head = newSong;
        m_tail = newSong;
    }
    else
    {
        //m_next of last node points to the new node, inserts node at end of list
        m_tail -> SetNext(newSong);
        //m_tail points to new node because it always points to the last node
        m_tail = newSong;
    }
    //m size increases by 1 in size
    m_size++;
}
// Name: GetPlaylistDetails()
// Desc - Returns a song object from a specific location
// Preconditions - Playlist populated
// Postconditions - Returns the data (does not output it)
Song* Playlist::GetPlaylistDetails(int location)
{
    //creates temp pointer variable
    Song* temp = m_head;
    //traverses through linked list
    for (int i = 0; i < m_size; i++)
    {
        //once location number is reached, the memory address for that targeted song object is returned
        if (i == location)
        {
            return temp;
        }
        temp = temp -> GetNext();
    }
    //if the location is not in range with the linked list size, nullptr is returned
    return temp;
}
// Name: Size
// Desc - Returns the m_size
// Preconditions - Playlist starts at size 0
// Postconditions - Returns the size
int Playlist::Size()
{
    return m_size;
}
// Name: PlayAt
// Desc - Passed the song that is to be played from the playlist
//       "Plays" a song by removing it from the playlist at a specific location
// Recommendations - Code this function last (dead last)
// Preconditions - Playlist has been populated
// Hint: Do not forget about removing from the front, middle, or end of the list
//       Could also remove the only node
// Postconditions - Playlist is reduced in size by one based on which song is played
void Playlist::PlayAt(int location)
{
    Song* curr = m_head;
    Song* prev = m_head;
    //special case: there is only one node in the list
    if (m_size == 1)
    {
        //deallocates first node
        delete m_head;
        //sets m_head and m_tail equal to nullptr
        m_head = nullptr;
        m_tail = nullptr;
    }
    //special case: there are multiple nodes in the list
    else
    {
        //special case: removing node from front
        if (location == 0)
        {
            //m_head points to the second node then first node gets deallocated
            m_head = m_head -> GetNext();
            delete prev;
        }
        //special case: removing node from end
        else if (location == m_size - 1)
        {
            //iterate until prev points to the second to last node and curr points to the last node
            while (curr -> GetNext() != nullptr)
            {
                prev = curr;
                curr = curr -> GetNext();
            }
            //last node gets deallocated, second to last node points to null, m_tail points to second to last node
            m_tail = prev;
            delete curr;
            prev -> SetNext(nullptr);
        }
        //special case: removing node from middle
        else
        {
            //iterate until the desired node is targeted
            for (int i = 0; i < location; i++)
            {
                prev = curr;
                curr = curr -> GetNext();
            }
            //node previous to chosen node points to the node in front of the chosen node, chosen node is deallocated
            prev -> SetNext(curr -> GetNext());
            delete curr;
        }
    }
    //m size decreases by 1
    m_size--;
}
/*
private instance variables:
Song* m_head; //Head of the playlist
Song* m_tail; //End of the playlist
int m_size; //Total songs on the playlist (size of linked list)
*/