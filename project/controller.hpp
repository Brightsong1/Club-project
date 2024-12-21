#pragma once

#include "command.hpp"
#include "observer.hpp"

// controller - connect input file with commands
class ControllerFabric
{
private:
    ObserverFileSys* obs;
    State* state;
public:
    ControllerFabric(ObserverFileSys* obs, State* state) : obs(obs), state(state) {}    
    void ClubLogicInit (std::ifstream& file);                                           
    Command* commandCreate (Event event);                                               // create command from event 
    Event commandExecute (Command* command, int time);                                  // execute command
    void eventsRead (std::ifstream& file);                                              // main cycle
    ~ControllerFabric() {};
};

// enum for traslate event to command
enum class EventsID {EnterCommand = 1, EnterTableCommand = 2, WaitCommand = 3, LeaveCommand = 4, EndWorkCommand = 11, EndWaitCommand = 12, ErrorCommand = 13};