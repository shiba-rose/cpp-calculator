#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "token.h"
#include <istream>
#include <unordered_map>

const std::string numbers = ".0123456789";


inline const std::unordered_map<char, Kind> operations = {
    {'(', Kind::left_parenthesis},
    {')', Kind::right_parenthesis},
    {'+', Kind::plus},
    {'-', Kind::minus},
    {'*', Kind::multiply},
    {'/', Kind::divide},
    {'%', Kind::remainder},
    {';', Kind::semicolon},
    {'=', Kind::assign}
};

inline const std::unordered_map<Kind, char> reverse_operations = [] {
    std::unordered_map<Kind, char> result;

    for (const auto& [ch, kind] : operations) {
        result[kind] = ch;
    }

    return result;
}();

const std::unordered_map<std::string, Kind> keywords = {
    {"let", Kind::let},
    {"quit", Kind::quit},
    {"const", Kind::constant},
    {"unconst", Kind::unconst},
    {"help", Kind::help},
    {"sin", Kind::sine},
    {"cos", Kind::cosine},
    {"tg", Kind::tangent},
    {"deg", Kind::degrees},
    {"rad", Kind::radians},
    {"calculate", Kind::calculate},
    {"global", Kind::global},
    {"local", Kind::local}
};

// Reads tokens from the input and supports one-token buffering.

class Token_stream {
    std::istream* stream;
    bool full;
    Token buffer;

public:
    Token_stream() : stream(nullptr), full(false), buffer() { }
    Token get();
    std::string get_file_path();

    void set_input(std::istream& s) {
        stream = &s;
        full = false;
    }
    
    void unget(Token t) { buffer = t; full = true; }
    void ignore(Kind c);
};


#endif