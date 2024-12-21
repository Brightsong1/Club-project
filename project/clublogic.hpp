#pragma once
#include "observer.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


// Business logic

class ClubLogic : public Observer, public ObserverFileSys
{
private:
    FileSystem filesys;                                 // filesystem
    std::ifstream* file;

    int timestart;
    int timeend;
    int hourcost;

    std::queue<std::string> queue;                      // queue of clients
    std::vector<std::string> clientdatabse;             // all clients in club
    std::vector<std::string> tabledatabase;             // name of now client for tables
    std::vector<int> tabletime;                         // time start using for every table
    std::vector<int> tablebusytime;                     // summary time using for every table
    std::vector<int> tablecost;                         // cost for every table

public:
    ClubLogic() : timestart(0), timeend(0), hourcost(0), file(nullptr) {filesys = FileSystem();}
    ~ClubLogic() { file->close(); }

    // init BL from config file
    void initcl (std::ifstream& file) override;

    // BL methods
    Event eventRead (std::ifstream& file) override;                     // read next event from file
    int timeCheck (int time) override;                                  // check if time of event is in time range of club
    int tableEnter(int TableID, int time, std::string name) override;  
    int tableLeave(int TableID, int time) override;                     // leave table with checking empty of queue
    bool clientCheck(std::string name) override;                        // find client in club
    void clubClose() override;                                         

    // getters
    std::vector<std::string>& databaseGet() override {return this->clientdatabse;}
    std::vector<std::string>& tabledatabaseGet() override {return this->tabledatabase;}
    std::queue<std::string>& queueGet() override {return this->queue;}
    std::vector<int>& tabletimesGet() override {return this->tabletime;}
    std::vector<int>& tablebusytimesGet() override {return this->tablebusytime;}
};

