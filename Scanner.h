#pragma once
#include<list>
#include <string>
#include "Clox.h"  
#include "Token.h"
#include <unordered_map>
using namespace std;

class Scanner {
protected:
    string source;
    list<Token> tokens;
    long int start = 0, current = 0, line = 1;

    bool isEnd();
    void addToken(TokenType type, any literal);
    void addToken(TokenType type);
    bool match(char expect);
    void stringCase();
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    void identifier();
    void number();
    static unordered_map<string, TokenType> keywords;
    

public:
    Scanner(string source);    
    void scanToken();
    list<Token> scanTokens();
    static void initializeKeywords();
};

