/*
** File: Processor.cpp
** Assignment Name: Project 5 – UMBC Process Manager
** Author: Nikki Cayas
** Date: 12/5/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Processor class
*/

#include "Processor.h"

// Name: Overloaded Constructor
// Desc: Sets m_fileName based on passed string
// Precondition: None
// Postcondition: m_fileName is populated
Processor::Processor(string filename)
{
    m_fileName = filename;
}
// Name: Destructor
// Desc: Deallocates memory allocated for the Processes.
// Precondition: A Processor exists.
// Postcondition: All dynamically allocated memory in Processor is deleted.
Processor::~Processor()
{
    //iterates through entire m_processes vector
    for (unsigned int i = 0; i < m_processes.size(); i++)
    {
        //delete each process pointer in the vector
        delete m_processes.at(i);
    }
    //clears the m_processes vector
    m_processes.clear();
    //iterates through entire m_threads vector
    for (unsigned int i = 0; i < m_threads.size(); i++)
    {
        //delete each process pointer in the vector
        delete m_threads.at(i);
    }
    //clears the m_threads vector
    m_threads.clear();
}
// Name: InitializeProcessor
// Desc: Starts the processor. Calls DisplayTitle and LoadProcesses.
//       Then calls PopulateThreads which adds all processes to each thread based on their calls
//       Calls MainMenu until quit. When quit, thanks user for using tool.
// Precondition: A Processor exists.
// Postcondition: Exits
void Processor::InitializeProcessor()
{
    //calls DisplayTitle()
    DisplayTitle();
    //calls LoadProcesses() to fill m_processes vector
    if (LoadProcesses(m_fileName))
    {
        //if the file is read and loaded successfully, then the threads are populated and main menu is called
        PopulateThreads();
        MainMenu();
    }
    //thank you message displayed
    cout << "Thank you for trying UMBC Processor!" << endl;
}
// Name: LoadProcesses
// Desc: Input file contains process name, id, call_id, and duration
//       Loads all processes into m_processes dynamically
//       For each thread defined in NUM_THREADS (which can be 1-6 for testing),
//       call AddThread and add the corresponding Process to that thread
//       For example, for 2 threads, AddThread(Process 0), AddThread (Process 1) would be called
//       Input files can have ANY number of processes (not limited to 52)
//       Assume input file will have processes >= number of threads)
// Precondition: m_fileName populated
// Postcondition: Returns true if file was read. Otherwise, it returns false.
bool Processor::LoadProcesses(string filename)
{
    //declares strings that store data from text file
    string name, id, call, duration;
    //declares input stream and opens file
    ifstream inputStream(filename);
    //checks to see if there is more content in the text file
    while (getline(inputStream, name, DELIMITER))
    {
        //reads in each song's instance variable and stores it in the local vars
        getline(inputStream, id, DELIMITER);
        getline(inputStream, call, DELIMITER);
        getline(inputStream, duration);
        //adds the dynamically allocated process to the m_processes vector
        m_processes.push_back(new Process(name, stoi(id), stoi(call), stoi(duration)));
    }
    //closes file
    inputStream.close();
    //adds the starting process for each thread
    for (int i = 0; i < NUM_THREADS; i++)
    {
        AddThread(m_processes.at(i));
    }
    //returns true if file was successfully read and false if file wasnt successfully read
    return !(inputStream.is_open());
}
// Name: AddThread
// Desc: Each Thread uses an Lstack. This function adds a new Thread to m_threads
//       The passed process is the "base" process that triggers all other function calls
//       For each thread in NUM_THREADS, a new thread is inserted into m_threads
// Precondition: m_threads isn't at capacity
// Postcondition: Add thread to m_threads with starting process
void Processor::AddThread(Process* p)
{
    //dynamically allocates new Lstack
    Lstack<Process*>* newLstack = new Lstack<Process*>();
    //pushes the process pointer into the lstack, acts as the "base" process
    newLstack -> Push(p);
    //pushes the lstack into the m_threads vector
    m_threads.push_back(newLstack);
}
// Name: GetProcessCalled
// Desc: Passed process ID and returns index of location in m_processes
//       Used with PopulateThreads
// Precondition:
// Postcondition: Returns index of location or -1 if not found
int Processor::GetProcessCalled(int id)
{
    //iterates through m_processes vector
    for (int i  = 0; i < (int)m_processes.size(); i++)
    {
        //if the passed process ID is found, the index of that process is returned
        if (m_processes.at(i) -> m_id == id)
        {
            return i;
        }
    }
    //if the passed process ID isnt found, -1 is returned
    return -1;
}
// Name: PopulateThreads
// Desc: Starting with provided process, follows the m_call to push next process onto stack
//       Uses GetProcessCalled to find the index of the process to add to the stack
//       Keeps adding processes until the m_call == -1
// Precondition: m_processes populated and first process of thread populated
// Postcondition: Populates number of threads provided in (NUM_THREADS)
void Processor::PopulateThreads()
{
    //creates local variables that keeps track of the id and index
    int id = 0;
    int index = 0;
    //iterates through m_threads vector
    for (unsigned int i = 0; i < m_threads.size(); i++)
    {
        //retrieves call id of the "top" of each lstack, acts as the starting or base id call
        id = ((m_threads.at(i) -> Top()) -> m_call);
        //iterates the pushing of processes until the id of the last process to be pushed is -1
        while (id != -1)
        {
            //finds index of the process to add to the stack using the previous call id
            index = GetProcessCalled(id);
            //pushes the next "called" process into the corresponding lstack
            m_threads.at(i) -> Push(m_processes.at(index));
            //updates the id with the call id of the new "top" process
            id = ((m_threads.at(i) -> Top()) -> m_call);
        }
    }
}
// Name: MainMenu
// Desc: Presents user with menu options for showing threads and allowing
// user to start the threads to processes.
// Precondition: Processes and threads have been loaded.
// Postcondition: The main menu is presented (Display Thread, Start Threads, Quit)
void Processor::MainMenu()
{
    //creates local tracker variables
    int userChoice = 0;
    bool quit = false;
    //main while loop, exits when user chooses to quit (inputs 3)
    while (!quit)
    {
        //displays menu
        cout << "Choose an option." << endl;
        cout << "1. Display Threads" << endl;
        cout << "2. Start Thread" << endl;
        cout << "3. Quit" << endl;
        cin >> userChoice;
        //checks for input validation (userChoice must be between 1-3)
        while (userChoice > 3 || userChoice < 1)
        {
            cout << "Please enter a valid option." << endl;
            cout << "Choose an option." << endl;
            cout << "1. Display Threads" << endl;
            cout << "2. Start Thread" << endl;
            cout << "3. Quit" << endl;
            cin >> userChoice;
        }
        //executes user's choice based on the number they input
        switch (userChoice)
        {
            case 1:
                DisplayThread();
                break;
            case 2:
                StartThreads();
                break;
            case 3:
                quit = true;
                break;
        }
    }
}
// Name: DisplayProcesses
// Desc: Displays all processes loaded from file (TESTING ONLY)
//       Used to make sure that all processes have been loaded correctly (Not used otherwise)
// Precondition: m_processes has been populated
// Postcondition: All processes are printed to the screen.
void Processor::DisplayProcesses()
{
    //iterates through m_processes vector
    for (unsigned int i = 0; i < m_processes.size(); i++)
    {
        //prints out each process
        cout << *(m_processes.at(i)) << endl;
    }
}
// Name: ListThreads
// Desc: Displays a numbered list of all threads listed with the number of processes
// Precondition: m_threads is populated
// Postcondition: None
void Processor::ListThreads()
{
    //iterates through m_threads vector
    for (unsigned int i = 0; i < m_threads.size(); i++)
    {
        //prints out the size of each lstack in the m_thread vector
        cout << i + 1 << ". Thread " << i + 1 << " (" << m_threads.at(i) -> GetSize() << " processes)" << endl;
    }

}
// Name: ChooseThread
// Desc: Allows a user to choose one of the threads to view. Calls ListThreads and
//       allows user to choose one. Returns value - 1 (location in vector)
// Precondition: A Thread exists.
// Postcondition: Returns value entered minus one
int Processor::ChooseThread()
{
    int choice = 0;
    //takes in user's input for which thread they would like to view
    do
    {
        ListThreads();
        cout << "What thread would you like to view?" << endl;
        cin >> choice;
    }
    //input validation, choice must be between 1 and the total number of threads
    while(choice < 1 || choice > (int)m_threads.size());
    //return user's choice
    return choice;
}
// Name: DisplayThreads
// Desc: Calls ChooseThread then Displays all processes in thread chosen
// Precondition: m_threads populated
// Postcondition: All processes for chosen thread displayed to screen
void Processor::DisplayThread()
{
    //calls ChooseThread() and displays the thread chosen by the user
    int thread = ChooseThread();
    //iterates through the chosen lstack
    for (int i = 0; i < m_threads.at(thread - 1) -> GetSize(); i++)
    {
        //displays each process in the chosen lstack using the friend overloaded operator
        cout << *(m_threads.at(thread - 1) -> At(i)) << endl;
    }
}
// Name: StartThread
// Desc: Starts all populated threads (based on size of m_threads)
// Keeps running total of duration of each process being processed
// Adds the duration from the "Top" of the thread then removes the process from the thread
// After all processes have been managed for all threads
//       displays total duration, in milliseconds, for each thread
// Precondition: m_processes has been populated
// Postcondition: Returns to main menu but all threads have 0 processes each
void Processor::StartThreads()
{
    //creates local variable to keep track of the total duration for each thread
    int totalTime = 0;
    //iterates through the m_threads vector
    for (unsigned int i = 0; i < m_threads.size(); i++)
    {
        //iterates through all the nodes in the lstack
        while (m_threads.at(i) -> GetSize() != 0)
        {
            //adds the duration value of each process in the lstack
            totalTime += m_threads.at(i) -> Top() -> m_duration;
            //removes each process in the lstack
            m_threads.at(i) -> Pop();
        }
        //displays the total duration for each thread
        cout << "Thread " << i + 1 << " took " << totalTime << " milliseconds to complete" << endl;
        //resets totaltime variable back to 0 for next lstack
        totalTime = 0; 
    }
}
// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
void Processor::DisplayTitle()
{
    cout << "Welcome to UMBC Processor!" << endl;
}

/*
private:
vector<Process* > m_processes; //Holds all processes loaded from file
vector<Lstack<Process*>* > m_threads; //A vector of multiple Lstacks (threads)
string m_fileName; //Filename to be loaded
*/