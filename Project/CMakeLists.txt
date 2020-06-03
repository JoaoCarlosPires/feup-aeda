cmake_minimum_required(VERSION 3.15)
project(feup_aeda_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(feup_aeda_project
        files/portugal.txt
        files/Portugalcalled0.txt
        files/Portugalcompetition.txt
        files/Portugalgames0.txt
        files/Portugalplayers.txt
        files/Portugalstaff.txt
        files/staff.txt
        bst.h
        Coach.cpp
        Coach.h
        Competition.cpp
        Competition.h
        Date.cpp
        Date.h
        Game.cpp
        Game.h
        input_utils.h
        main.cpp
        Menus.cpp
        Menus.h
        Person.cpp
        Person.h
        Player.cpp
        Player.h
        Provider.cpp
        Provider.h
        Staff.cpp
        Staff.h
        Statistics.cpp
        Statistics.h
        Team.cpp
        Team.h
        utils.h)
