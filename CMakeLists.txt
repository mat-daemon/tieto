cmake_minimum_required(VERSION 2.8.10)
project(Tieto_game)

set(SOURCE_FILES main.cpp reader.cpp individual.cpp commands.cpp commander.cpp
advisor.cpp attack_advisor.cpp defense_advisor.cpp mine_advisor.cpp)

add_executable(play ${SOURCE_FILES})