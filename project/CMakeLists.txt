cmake_minimum_required(VERSION 3.10)

project(ClubProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(
    SOURCES
    main.cpp
    filesys.cpp           
    clublogic.cpp     
    command.cpp                  
    controller.cpp         
)

add_executable(Myprj ${SOURCES})
install(TARGETS Myprj DESTINATION bin)

set(CMAKE_CXX_COMPILER "g++") 

set_target_properties(Myprj PROPERTIES
    VERSION 1.0
    SOVERSION 1
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)