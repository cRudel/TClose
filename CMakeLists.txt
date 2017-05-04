cmake_minimum_required(VERSION 3.7)
project(TClose)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ._graphio.h
        graph.c
        graph.h
        graphio.c
        graphio.h
        tclose.c
        tclose.h
        testtclose.c)

add_executable(TClose ${SOURCE_FILES})