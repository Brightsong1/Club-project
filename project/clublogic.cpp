#include "clublogic.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>

// init BL
void ClubLogic::initcl (std::ifstream& file) 
{
    this->file = (std::ifstream*)&file;
    int numtable = this->filesys.numRead(file);
    this->timestart = this->filesys.timestartRead(file);

    // print start time
    std::cout << formatTime(this->timestart) <<std::endl;

    this->timeend = this->filesys.timeendRead(file);
    this->hourcost = this->filesys.numRead(file);  

    // reserve memory for count of tables
    for (int i = 0; i<numtable; i++)
    {
        this->tabletime.push_back(0);
    }
    this->tablecost = std::vector<int>(numtable, 0);
    this->tablebusytime = std::vector<int>(numtable, 0);
    this->tabledatabase = std::vector<std::string>(numtable, "");
}

// reading next event
Event ClubLogic::eventRead (std::ifstream& file) 
{
    return this->filesys.eventRead(file);
}

// check time of event
int ClubLogic::timeCheck (int time) 
{
    if(time >= this->timeend || time < this->timestart)
    {
        return -1;
    }
    return 1;
}

// enter table
int ClubLogic::tableEnter(int TableID, int time, std::string name) 
{
    // check if table is free
    if(this->tabletimesGet()[TableID] != 0)
    {
        return -1;
    }
    this->tabledatabase[TableID] = name;    // save name of client
    this->tabletimesGet()[TableID] = time;  // save time enter
    return 1;
}

// leave table
int ClubLogic::tableLeave(int TableID, int time) 
{
    // check if table is busy
    if(this->tabletimesGet()[TableID] == 0)
    {
        return -1;
    }

    this->tabledatabase[TableID] = "";

    // calculate statistic 
    // time busy
    int h = time - this->tabletimesGet()[TableID];
    this->tabletimesGet()[TableID] = 0;
    this->tablebusytimesGet()[TableID] += h;

    // cost
    if ( h%60 != 0 ) 
    { 
        h = h/60 + 1;
    }
    else 
    {
        h = h/60; 
    }
    this->tablecost[TableID] = this->tablecost[TableID] + h * this->hourcost;

    // check queue
    if(!this->queue.empty())
    {
        return 0;
    }

    return 1;
}

// find client 
bool ClubLogic::clientCheck(std::string name)
{
    if(std::find(this->clientdatabse.begin(), this->clientdatabse.end(), name) != this->clientdatabse.end())
    {
        return true;
    }
    return false;
}

// close club
void ClubLogic::clubClose()
{
    // print event 11 for all client in club
    for(int i = 0; i < this->clientdatabse.size(); i++)
    {
        std::cout << formatTime(this->timeend) << " 11 " << this->clientdatabse[i] << std::endl;
        this->clientdatabse[i] = "";
    }
    // print end time
    std::cout << formatTime(this->timeend) << std::endl;
    
    // print statistic and leave tables
    for(int i = 0; i < this->tablecost.size(); i++)
    {
        this->tableLeave(i, this->timeend);
        std::cout << i+1 << " " << this->tablecost[i] << " " << formatTime(this->tablebusytimesGet()[i]) << std::endl;
    }
}

// format time from int to %02d:%02d
std::string formatTime(int time) {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << time / 60 << ":"
        << std::setw(2) << std::setfill('0') << time % 60;
    return oss.str();
}