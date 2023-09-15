/*
** File: proj1.cpp
** Assignment Name: Project 1 – Hashtag Analyzer
** Author: Nikki Cayas
** Date: 9/17/22
** Course/ Section: CMSC 202 Section 50/52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This project is a hashtag analyzer that will parse a file of messages and a file of hashtags to see if the hashtags are used in the messages. It will then count the number of times the hashtag exists in the messages and display them.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ARRAY_SIZE = 20; //max array size for hashtag, message, and count arrays

//Pre-condition: The user must input an existing text file for this function to work. This text file cannot contain more than 20 hashtags.
//Post-condition: The array of hashtags is now filled with no more than 20 hashtag elements. 
//The total number of non-default elements in the hashtag array is returned and stored into a variable. 
int loadHashtagFile(string hashtagsArray[MAX_ARRAY_SIZE]);

//Pre-condition: The user must input an existing text file for this function to work. This text file cannot contain more than 10 messages (20 lines).
//Post-condition: The array of messages is now filled with no more than 10 message elements. 
//The total number of non-default elements in the message array is returned and stored into a variable. 
int loadMessageFile(string messagesArray[MAX_ARRAY_SIZE]);

//Pre-condition: The arrays for hashtags and messages have non-default string values. The total number of messages and hashtags has been initialized. 
//The array that keeps match count of each hashtag has been initialized to 0 values. 
//Post-condition: The array that keeps count of each hashtag's match is now updated with the appropriate values. 
void processMessages(string hashtagsArray[MAX_ARRAY_SIZE], string messagesArray[MAX_ARRAY_SIZE], int hashtagCountArray[MAX_ARRAY_SIZE], int htTotalCount, int mTotalCount);

//Pre-condition: All three arrays either have "garbarge" values, default values, or values from previous runs as their elements.
//Post-condition: All three arrays are now filled with their default type values. 
void resetsData(string hashtagsArray[MAX_ARRAY_SIZE], string messagesArray[MAX_ARRAY_SIZE], int hashtagCountArray[MAX_ARRAY_SIZE]);

//Pre-condition: All arrays have been declared and initialized with appropriate values from the text files. 
//Post-condition: No values are changed, just printed. The values that are printed include: each hashtag and its count for matches.
void displayCount(string hashtagsArray[MAX_ARRAY_SIZE], int hashtagCountArray[MAX_ARRAY_SIZE], int htTotalCount);

int main()
{

  string hashtagsArray[MAX_ARRAY_SIZE]; //declares array for hashtags
  string messagesArray[MAX_ARRAY_SIZE]; //declares array for messages
  int hashtagCountArray[MAX_ARRAY_SIZE] = {0}; //declares and initializes array that tracks num of times each hashtag appears in the messages
  
  //prints welcome message and instructions
  cout << "\nWelcome to the Hashtag Analyzer!" << endl;
  cout << "You will choose a file of hashtags to search for." << endl;
  cout << "Then, you will choose a file to search for the hashtags." << endl;

  //main do while loop that repeats depending on user's choice to repeat game
  bool repeatGame = true;
  do 
  {
    //resets array data to default "0" values
    resetsData(hashtagsArray, messagesArray, hashtagCountArray);

    //declares & initializes total count of hashtags and messages in the files to respective variables by loading files
    int hashtagTotalCount = loadHashtagFile(hashtagsArray);
    int messageTotalCount = loadMessageFile(messagesArray);

    //displays total count of hashtags and messages in each file
    cout << hashtagTotalCount << " hashtags loaded." << endl;
    cout << messageTotalCount/2 << " messages loaded." << endl;

    //processes the messages, displays the messages that match with hashtags
    processMessages(hashtagsArray, messagesArray, hashtagCountArray, hashtagTotalCount, messageTotalCount);

    //displays the count for each hashtag's matches
    displayCount(hashtagsArray, hashtagCountArray, hashtagTotalCount);

    //determines whether or not to end program based on user's choice to analyze another file
    char userChoice;
    cout << "Would you like to analyze another file? (y/n) " << endl;
    cin >> userChoice;
    if (userChoice == 'n')
    {
      repeatGame = false;
    }
  }
  while(repeatGame);

  //ends program
  cout << "\nThank you for using the hashtag analyzer!" << endl;
  return 0;
}

int loadHashtagFile(string hashtagsArray[])
{
  //takes in hashtag file from user, declares input stream, opens file
  string hashtagFile;
  cout << "\nPlease enter the file with the hashtags you would like to use: " << endl;
  cin >> hashtagFile;
  ifstream inputStream1;
  inputStream1.open(hashtagFile);

  //checks input validity, determines if file exists, reprompts user if file doesnt exist
  while (!(inputStream1.is_open()))
  {
    cout << "\nThis file cannot be found. Please enter an existing file with the hashtags you would like to use: " << endl;
    cin >> hashtagFile;
    inputStream1.open(hashtagFile);
  }
  cout << "\nYour file was imported!" << endl;

  //counts number of hashtags in this file & fills hashtag array with hashtag elements
  string hashtag;
  int hashtagCount = 0;
  while (inputStream1 >> hashtag)
  {
    hashtagsArray[hashtagCount] = hashtag;
    hashtagCount++;
  }

  //closes file and returns number of total hashtags
  inputStream1.close();
  return hashtagCount;
}

int loadMessageFile(string messagesArray[])
{
  //takes in messages file from use, declares input stream, opens file
  string messageFile;
  cout << "\nPlease enter the file with the messages you would like to parse: " << endl;
  cin >> messageFile;
  ifstream inputStream2;
  inputStream2.open(messageFile);

  //checks input validity, determines if file exists, reprompts user for another file if nonexistent
  while (!(inputStream2.is_open()))
  {
    cout << "\nThis file cannot be found. Please enter an existing file with the messages you would like to parse: " << endl;
    cin >> messageFile;
    inputStream2.open(messageFile);
  }
  cout << "\nYour file was imported!" << endl;

  //counts number of messages in this file, fills messsage array with message elements
  string message;
  int messageCount = 0;
  while (getline(inputStream2, message))
  {
    messagesArray[messageCount] = message;
    messageCount++;
  }

  //closes file and returns number of total messages
  inputStream2.close();
  return messageCount;
}

void processMessages(string hashtagsArray[], string messagesArray[], int hashtagCountArray[], int htTotalCount, int mTotalCount)
{
  cout << "\nMessages with matching hashtags: " << endl;
  int totalMatchesCount = 0;

  //traverses parallel arrays, checking to see if any of the hashtags appear in any of the messages
  for (int i = 0; i < htTotalCount; i++)
  {
    for (int j = 0; j < mTotalCount; j+=2)
    {
      if (hashtagsArray[i] == messagesArray[j])
      {
        //respective hashtag and message are displayed and the third array (keeps match count of each hashtag) updates
        totalMatchesCount++;
        hashtagCountArray[i] += 1;
        cout << totalMatchesCount << ". " << messagesArray[j] + " " + messagesArray[j+1] << endl;
      }
    }
  }
}

void resetsData(string hashtagsArray[], string messagesArray[], int hashtagCountArray[])
{
  for (int i = 0; i < MAX_ARRAY_SIZE; i++)
  {
    //all elements in each array are reset to their default "0" value
    hashtagsArray[i] = "";
    messagesArray[i] = "";
    hashtagCountArray[i] = 0;
  }
}

void displayCount(string hashtagsArray[], int hashtagCountArray[], int htTotalCount)
{
  for (int i = 0; i < htTotalCount; i++)
  {
    //displays each hashtag number, hashtag itself, and its count of matches
    cout << setw(5) << (i+1) << setw(25) << hashtagsArray[i] << setw(4) << hashtagCountArray[i] << endl;
  }
}