cmake_minimum_required(VERSION 3.10)

project(Calculator
    VERSION 1.0
    LANGUAGES CXX
)

set(HEADERS
    sourse/calculator.h
    sourse/Token.h
    sourse/Token_stream.h
    sourse/grammar.h
    sourse/utility.h
    sourse/variable.h
)

set(SOURCES
    sourse/calculator.cpp
    sourse/Token.cpp
    sourse/Token_stream.cpp
    sourse/utility.cpp
    sourse/variable.cpp
    sourse/grammar.cpp
    sourse/main.cpp
)

set(executable_name calculator)

add_executable(${executable_name} ${SOURCES} ${HEADERS})

