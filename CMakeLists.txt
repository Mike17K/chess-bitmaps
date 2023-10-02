cmake_minimum_required(VERSION 3.0)
project(chess)

# Add the "Package" folder to the list of include directories
include_directories(Package)

# Create a list of source files for the project
set(SOURCES 
    main.cpp
    Package/Constands/constands.h
    Package/Constands/Night.h

    Package/Helpers/Display/display.h
    Package/Helpers/Display/display.cpp

    Package/Helpers/BitFunctions/bitFunctions.h
    Package/Helpers/BitFunctions/bitFunctions.cpp   

    Package/Tools/Board/board.h 
    Package/Tools/Board/board.cpp 
)

# Add the source files to the executable
add_executable(run ${SOURCES})
