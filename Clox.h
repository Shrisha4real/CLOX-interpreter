#pragma once
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include "AstPrinter.h"
#include "Expr.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

class Clox {
public:
    
    static bool hadError;

    static void run(const string& source);
    static void report(int line, const string& where, const string& message);
    static void error(const Token* token, const string& message);
    static void runFile(const string& filename);
    static void readPrompt();
};

