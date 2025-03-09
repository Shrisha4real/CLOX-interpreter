#pragma once
#include <string>
#include <iostream>
#include <list>
using namespace std;


class Clox {
public:
    
    static bool hadError;

    static void read(const string& source);
    static void report(int line, const string& where, const string& message);
    static void error(int line, const string& message);
    static void runFile(const string& filename);
    static void readPrompt();
};

