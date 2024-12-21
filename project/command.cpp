#include "command.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <sstream>

Event State::commandExecute(Command* command, int time)
{
    return command->execute(this->obs);
}


// enter club command
Event EnterCommand::execute(Observer* obs)
{
    // print event
    std::cout << formatTime(this->time) << " 1 " << this->name << std::endl;
    // check work time club
    if(obs->timeCheck(this->time) == -1)
    {
        return Event{this->time, 13, "NotOpenYet"};
    }
    // check clint in club
    if(obs->clientCheck(this->name))
    {
        return Event{this->time, 13, "YouShallNotPass"};
    }
    // add to base of nowclients
    obs->databaseGet().push_back(this->name);
    return Event{0, -1, ""};
}

// enter table command
Event EnterTableCommand::execute(Observer* obs)
{
    // in file tableid start from 1
    this->TableID -=1;

    // print event
    std::cout << formatTime(this->time) << " 2 " << this->name << " " << this->TableID+1 << std::endl;

    // check client in club
    if(!obs->clientCheck(this->name))
    {
        return Event{this->time, 13, "ClientUnknown"};
    }
    // check free table
    if(obs->tableEnter(this->TableID, this->time, this->name) == -1)
    {
        return Event{this->time, 13, "PlaceIsBusy"};
    }
    return Event{0, -1, ""};
}

Event WaitCommand::execute(Observer* obs)
{
    // print event
    std::cout <<formatTime(this->time) << " 3 " << this->name << std::endl;

    // check free table
    for (int i = 0; i != obs->tabletimesGet().size(); i++)
    {
        if (obs->tabletimesGet()[i] == 0)
        {
            return Event{this->time, 13, "ICanWaitNoLonger"};
        }
    }

    // check queue size
    if (obs->queueGet().size() < obs->tablebusytimesGet().size())
    {
        obs->queueGet().push(this->name);
        return Event{0, -1, ""};
    }

    std::cout << formatTime(this->time) << " 11 " << this->name << std::endl;
    obs->databaseGet().erase(std::find(obs->databaseGet().begin(), obs->databaseGet().end(), this->name));
    return Event{0, -1, ""};
}

// leave command
Event LeaveCommand::execute(Observer* obs)
{
    // print event
    std::cout << formatTime(this->time) << " 4 " << this->name << std::endl;

    // check client in club
    if(!obs->clientCheck(this->name))
    {
        return Event{this->time, 13, "ClientUnknown"};
    }

    // delete from database
    obs->databaseGet().erase(std::find(obs->databaseGet().begin(), obs->databaseGet().end(), this->name));
    
    Event res = Event{0, -1, ""};
    // find client table if it exists
    auto pos = std::find(obs->tabledatabaseGet().begin(), obs->tabledatabaseGet().end(), this->name);

    if (pos != obs->tabledatabaseGet().end())
    {
        int flag = obs->tableLeave(std::distance(obs->tabledatabaseGet().begin(), pos), this->time);
        if (flag == 0 )
        {
            int numtable = std::distance(obs->tabledatabaseGet().begin(), pos);
            std::string newclient = obs->queueGet().front();
            obs->queueGet().pop();
            // first client in queue enter table
            res = Event{this->time, 12, newclient + " " + std::to_string(numtable+1)};
        }
    }   
    return res;
}

// end work command
Event EndWorkCommand::execute(Observer* obs)
{
    obs->clubClose();
    return Event{0, -1, ""};
}

// end wait command
Event EndWaitCommand::execute(Observer* obs)
{
    this->TableID -= 1;
    obs->tableEnter(this->TableID, this->time, this->name);
    std::cout << formatTime(this->time) << " 12 " << this->name << " " << this->TableID + 1 << std::endl;
    return Event{0, -1, ""};
}

// error command
Event ErrorCommand::execute(Observer* obs)
{
    std::cout << formatTime(this->time) << " 13 " << this->error << std::endl;
    return Event{0, -1, ""};
}