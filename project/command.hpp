#pragma once
#include "observer.hpp"

// pattern command
class Command
{
public:
    virtual Event execute(Observer* obs) = 0;
};

// pattern state for executing commands with club logic
class State
{
private:
    Observer* obs;
    bool flag;
public:
    State(Observer* observer) : obs(observer), flag(false) {}
    Event commandExecute(Command* command, int time);
};

// enter club command
class EnterCommand : public Command
{
private:
    int time;
    std::string name;
public:
    EnterCommand(int time, std::string name) : time(time), name(name) {}
    Event execute(Observer* obs) override;
};

// enter table command
class EnterTableCommand : public Command
{
private:
    int time;
    std::string name;
    int TableID;
public:
    EnterTableCommand(int time, std::string name, int TableID) : time(time), name(name), TableID(TableID) {}
    Event execute(Observer* obs) override;
};

// wait command
class WaitCommand : public Command
{
private:
    int time;
    std::string name;
public:
    WaitCommand(int time, std::string name) : time(time), name(name) {}
    Event execute(Observer* obs) override;
};

// leave club command
class LeaveCommand : public Command
{
private:
    int time;
    std::string name;
public:
    LeaveCommand(int time, std::string name) : time(time), name(name) {}
    Event execute(Observer* obs) override;
};

// end club work command
class EndWorkCommand : public Command
{
private:
    int time;
    std::string name;
public:
    EndWorkCommand(int time, std::string name) : time(time), name(name) {}
    Event execute(Observer* obs) override;
};

// end wait in queue
class EndWaitCommand : public Command
{
private:
    int time;
    std::string name;
    int TableID;
public:
    EndWaitCommand(int time, std::string name, int TableID) : time(time), name(name), TableID(TableID) {}
    Event execute(Observer* obs) override;
};

// error command
class ErrorCommand : public Command
{
private:
    int time;
    std::string error;
public:
    ErrorCommand(int time, std::string error) : time(time), error(error) {}
    Event execute(Observer* obs) override;
};

