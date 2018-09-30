cmake_minimum_required(VERSION 3.12)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife main.cpp Board.cpp Board.h ClassicBoard.cpp ClassicBoard.h RuntimeException.cpp RuntimeException.h MapFileMismatchException.cpp MapFileMismatchException.h DoughnutBoard.cpp DoughnutBoard.h MirrorBoard.cpp MirrorBoard.h GoLSimulation.cpp GoLSimulation.h)