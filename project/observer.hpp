#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "filesys.hpp"


// observer for controller
class ObserverFileSys
{
public:
    virtual void initcl (std::ifstream& file) = 0;
    virtual Event eventRead (std::ifstream& file) = 0;
};

// observer for commands
class Observer
{
public:
    virtual int timeCheck (int time) = 0;
    virtual int tableEnter(int TableID, int time, std::string name) = 0;
    virtual int tableLeave(int TableID, int time) = 0;
    virtual void clubClose() = 0;
    virtual std::vector<int>& tabletimesGet() = 0;
    virtual std::vector<std::string>& databaseGet () = 0;
    virtual std::vector<int>& tablebusytimesGet() = 0;
    virtual std::queue<std::string>& queueGet() = 0;
    virtual std::vector<std::string>& tabledatabaseGet() = 0;
    virtual bool clientCheck(std::string name) = 0;
};

std::string formatTime(int time);