# include "filesys.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <algorithm>

// print error in input file
void errorHande(std::ifstream& file, std::string error, int line)
{
    std::cout << error << line+4 << std::endl;
    file.close();
    exit(0);
}

// get int from file
int FileSystem :: numRead (std::ifstream& file)
{
    std::string buff;
    std::getline(file, buff);
    // remove crlf linux
    buff.erase(std::remove(buff.begin(), buff.end(), '\r'), buff.end());
    return std::stoi(buff);
}

// get time start from file
int FileSystem :: timestartRead (std::ifstream& file)
{
    int h,m;
    std::string buff;
    std::getline(file, buff);
    // remove crlf linux
    buff.erase(std::remove(buff.begin(), buff.end(), '\r'), buff.end());
    this->timestr = buff.substr(6,11);
    std::string hs, hm;
    hs = buff.substr(0,2);
    hm = buff.substr(3,5);
    h = std::stoi(hs);
    m = std::stoi(hm);

    // check correct time
    if(h*60 + m < 0 || h*60 + m > 1439)
    {
        errorHande(file,"Invalid time open club line: " , 2);
    }

    return h*60+m;
}

// get time end from file
int FileSystem :: timeendRead (std::ifstream& file)
{
    int h,m;
    std::string hs, hm;
    hs = this->timestr.substr(0,2);
    hm = this->timestr.substr(3,5);
    h = std::stoi(hs);
    m = std::stoi(hm);

    // check correct time
    if(h*60 + m < 0 || h*60 + m > 1439)
    {
        errorHande(file,"Invalid time close club line: " , 2);
    }

    return h*60+m;
}

// read event from file
Event FileSystem :: eventRead (std::ifstream& file)
{   
    Event res;
    std::string evstr;
    if(!std::getline(file, evstr))
    {
        res.id = -1;
        file.close();
        return res;
    }
    // remove crlf linux
    evstr.erase(std::remove(evstr.begin(), evstr.end(), '\r'), evstr.end());
    if(evstr.empty())
    {
        res.id = -1;
        file.close();
        return res;
    }
    std::string hs, hm, id, data;
    hs = evstr.substr(0,2);
    hm = evstr.substr(3,5);
    res.time = std::stoi(hs)*60+std::stoi(hm);

    // check time
    if(res.time < 0 || res.time > 1439)
    {
        errorHande(file, "Invalid time event in str: ", this->evid);
    }

    evstr = evstr.substr(6, evstr.length());

    // check name
    if(evstr.find(' ') == std::string::npos)
    {
        errorHande(file, "Invalid name in str: ", this->evid);
    }

    id = evstr.substr(0, evstr.find(' ')); 
    res.id = std::stoi(id);

    // check table id
    if(res.id == 2)
    {
        evstr = evstr.substr(evstr.find(' '), evstr.length());
        if(evstr.empty())
        {
            errorHande(file, "Invalid number of table in str: ", this->evid);
        }
    }

    res.data = evstr.substr(evstr.find(' ')+1, evstr.length()); 
    
    this->evid++;

    return res;
}