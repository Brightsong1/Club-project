#pragma once
#include <iostream>

// Structure for events
struct Event
{
    int time;
    int id;
    std::string data;
};

// Work with input file

class FileSystem
{
private:
    std::string timestr;
    int evid;
public:
    FileSystem() : timestr(""), evid(0) {}
    ~FileSystem() {}
    // Methods for reading defualt config
    int numRead (std::ifstream& file);
    int timestartRead (std::ifstream& file);
    int timeendRead (std::ifstream& file);

    // Method for reading event
    Event eventRead (std::ifstream& file);
};