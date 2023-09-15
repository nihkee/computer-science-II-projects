/*
** File: Process.cpp
** Assignment Name: Project 5 – UMBC Process Manager
** Author: Nikki Cayas
** Date: 12/5/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Process class
*/

#include "Process.h"

// Name: Default Constructor
// Desc: Constructs a process struct with default (-1, test, -1, -1)
// Precondition: None
// Postcondition: A new Process struct is created for use.
Process::Process()
{
    m_name = "test";
    m_id = -1;
    m_call = -1;
    m_duration = -1;
}
// Name: Overloaded Constructor
// Desc: Constructs a process struct given all fields.
// Precondition: Process created using passed data
// Postcondition: A new Process struct is created for use.
Process::Process(string name, int id, int call, int duration)
{
    m_name = name;
    m_id = id;
    m_call = call;
    m_duration = duration;
}

ostream& operator<<(ostream& output, Process& p1)
{
    output << p1.m_name << " " << p1.m_id << " " << p1.m_call << " " << p1.m_duration << endl;
    return output;
}
/*Member variables (all public)
string m_name; //Name of process
int m_id; // Process ID
int m_call; //Process called
int m_duration; //Duration of process
*/