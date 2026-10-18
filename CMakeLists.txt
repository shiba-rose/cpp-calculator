cmake_minimum_required(VERSION 3.10)

project(Calculator
    VERSION 1.0
    LANGUAGES CXX
)

set(HEADERS
    include/calculator/calculator.h
    src/internal/Token.h
    src/internal/Token_stream.h
    src/internal/grammar.h
    src/internal/utility.h
    src/internal/variable.h
)

set(SOURCES
    src/calculator.cpp
    src/Token.cpp
    src/Token_stream.cpp
    src/utility.cpp
    src/variable.cpp
    src/grammar.cpp
    src/main.cpp
)

set(executable_name calculator)

add_executable(${executable_name} ${SOURCES} ${HEADERS})



