cmake_minimum_required (VERSION 3.1.3)
set(PROJECT_NAME LangstonsAnt)  #Setting the project name to a variable for easy changeability
project (${PROJECT_NAME})

set(SFML_ROOT "C:/dev/SFML242/")    #Root directory of sfml goes here so that "FindSFML.cmake" can find it

add_executable (${PROJECT_NAME}     #Adding all the self-written source files
        ./Source/main.cpp
        ./Source/Application.cpp
        ./Source/Ant.cpp
        ./Source/ResourceManager/ResourceHolder.cpp
        ./Source/Util/Random.cpp
        ./Source/Util/FPSCounter.cpp
        ./Source/Native/Win32.cpp
        ./Source/Native/Unix.cpp)

#./Source/Util/Common.cpp
#this file doesn't even exist lol

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)   #Setting the C++ standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

file(COPY Res DESTINATION ${CMAKE_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Screenshots)

find_package(Threads)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Setting the Module path so you can find SFML with the "FindSFML.cmake" script, which is in there

find_package(SFML 2.4 REQUIRED network audio graphics window system) #Finding SFML
include_directories(${SFML_INCLUDE_DIR}) #So that It won't complain that it can't find <SFML/Graphics.hpp> for example

target_link_libraries(${PROJECT_NAME} Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ) #Linking external libs
