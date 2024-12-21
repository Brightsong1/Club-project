#include "controller.hpp"
#include "command.hpp"
#include <string>

// init club logic
void ControllerFabric::ClubLogicInit (std::ifstream& file)
{
    this->obs->initcl(file);
}

// fabric for commands
Command* ControllerFabric::commandCreate (Event event)
{
    EventsID eventid = EventsID(event.id);

    switch (eventid)
    {
    case EventsID::EnterCommand :
    {
        return new EnterCommand(event.time, event.data);
    }
    case EventsID::EnterTableCommand :
    {
        return new EnterTableCommand(event.time, event.data.substr(0, event.data.find(' ')), std::stoi(event.data.substr(event.data.find(' '), event.data.size())));
    }
    case EventsID::WaitCommand :
    {
        return new WaitCommand(event.time, event.data);
    }
    case EventsID::LeaveCommand :
    {
        return new LeaveCommand(event.time, event.data);
    }
    case EventsID::EndWorkCommand :
    {
        return new EndWorkCommand(event.time, event.data);
    }
    case EventsID::EndWaitCommand :
    {
        return new EndWaitCommand(event.time, event.data.substr(0, event.data.find(' ')), std::stoi(event.data.substr(event.data.find(' ')+1, event.data.size())));
    }
    case EventsID::ErrorCommand :
    {
        return new ErrorCommand(event.time, event.data);
    }
    default:
        return new ErrorCommand(event.time, "Unknown event");

    }
}

// execute commands
Event ControllerFabric::commandExecute (Command* command, int time)
{
    return this->state->commandExecute(command, time);
}

// main cycle for reading events
void ControllerFabric::eventsRead (std::ifstream& file)
{
    Event buffer;
    buffer.id = -2;
    while (true)
    {
        // if no error event
        if (buffer.id < 0)
        {
            // read new event from file
            buffer = this->obs->eventRead(file);
            // if last event - break
            if(buffer.data.empty())
            {
                break;
            }
        }
        Event res = this->state->commandExecute(this->commandCreate(buffer), buffer.time);
        buffer = res;
    }
    // end work command
    buffer.id = 11;
    this->state->commandExecute(this->commandCreate(buffer), buffer.time);
}