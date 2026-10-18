cmake_minimum_required(VERSION 3.10)

project(Calculator
    VERSION 1.0
    LANGUAGES CXX
)

set(HEADERS
    src/internal/calculator.h
    src/internal/token.h
    src/internal/token_stream.h
    src/internal/grammar.h
    src/internal/utility.h
    src/internal/variable.h
)

set(SOURCES
    src/calculator.cpp
    src/token.cpp
    src/token_stream.cpp
    src/utility.cpp
    src/variable.cpp
    src/grammar.cpp
    src/main.cpp
)

set(executable_name calculator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${executable_name} ${SOURCES} ${HEADERS})
target_include_directories(${executable_name} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/calculator"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/internal"
)


