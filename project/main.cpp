#include <iostream>
#include "controller.hpp"
#include "clublogic.hpp"
#include "observer.hpp"


int main(int argc, char*argv[])
{
    if(argc != 2)
    {
        std::cout << "Invalid num of args" << std::endl;
        exit(0);
    }

    std::string filename = argv[1];
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) { 
        std::cerr << "Error: File not found or could not be opened!" << std::endl;
        return 0;
    }
    ClubLogic CL;
    State state(&CL);
    ControllerFabric controller(&CL, &state);
    controller.ClubLogicInit(file);
    controller.eventsRead(file);
    
}