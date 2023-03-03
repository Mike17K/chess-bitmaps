cmake_minimum_required(VERSION 3.0)
project(chess)

# Add the "functions" folder to the list of include directories
include_directories(functions)

# Create a list of source files for the project
set(SOURCES 
    main.cpp
    functions/board.cpp
    functions/board.h
    functions/bitFunctions.cpp
    functions/bitFunctions.h
    functions/constands.h
    functions/display.cpp
    functions/display.h
    functions/Night.h
    
)

# Add the source files to the executable
add_executable(run ${SOURCES})
