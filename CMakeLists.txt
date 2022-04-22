cmake_minimum_required(VERSION 3.6.2)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads)

set(SOURCE_FILES
        main.cpp

        Exeptions.h

        Core.h
        Reader.h
        Commands.h

        Core.cpp
        Reader.cpp
        Commands.cpp

        CoreTests.cpp
        CommandsTests.cpp)

add_subdirectory(Google_tests)

include_directories(Google_tests/googletest/include)
include_directories(Google_tests/googlemock/include)

add_executable(interpreter ${SOURCE_FILES})

target_link_libraries(interpreter gtest gtest_main)
target_link_libraries(interpreter gmock gmock_main)

target_link_libraries(interpreter ${CMAKE_THREAD_LIBS_INIT})
