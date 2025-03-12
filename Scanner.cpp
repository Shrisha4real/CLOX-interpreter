#include "Scanner.h"
#include "Clox.h"   // Include the Clox class for error handling.
#include "Token.h"  // Include the Token class for managing tokens
#include <iostream>
#include <sstream>

using namespace std;
// Initialize the static keyword map for the Scanner class
unordered_map<string, TokenType> Scanner::keywords;

/**
 * Populates the keyword map with predefined Lox language keywords.
 * Maps keyword strings to their corresponding TokenType values.
 */
void Scanner::initializeKeywords() {
    keywords.insert({ "and",AND });
    keywords.insert({ "class",CLASS });
    keywords.insert({ "else" ,ELSE});
    keywords.insert({ "false",FALSE });
    keywords.insert({ "for",FOR });
    keywords.insert({ "fun",FUN });
    keywords.insert({ "if",IF});
    keywords.insert({ "or",OR });
    keywords.insert({ "print",PRINT });
    keywords.insert({ "return",RETURN});
    keywords.insert({ "super",SUPER });
    keywords.insert({ "this", THIS });
    keywords.insert({ "true",TRUE });
    keywords.insert({ "var",  VAR});
    keywords.insert({ "while",WHILE });
}

/**
 * Constructor for Scanner.
 * Initializes a scanner with the given source code.
 */
Scanner::Scanner(string source) : source(source) {
    tokens.clear();
    
}


//Checks if the scanner has reached the end of the source code.
bool Scanner::isEnd() {
    return (current >= source.length());
}


 //Adds a token to the token list with an optional literal value.
void Scanner::addToken(TokenType type, any literal) {
    int dif = (current - start == 0) ? 1 : (current - start);
    string text = source.substr(start, dif);
    tokens.emplace_back(type, text, literal, line);
}

//Adds a token to the token list without a literal value.
void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}

//Matches the current character with an expected character.
bool Scanner::match(char expect) {
    if (isEnd()) return false;
    if (source.at(current) == expect) {
        current++;
        return true;
    }
    return false;
}

/**
 * Handles string literals in the source code.
 * Extracts the string content and adds a STRING token.
 */
void Scanner::stringCase() {
    while (!isEnd() && source.at(current) != '"') {
        if (source.at(current) == '\n')
            line++;
        current++;
    }
    if (isEnd()) {
        cerr << line << " Unterminated string\n";
    }
    current++;
    string s = source.substr(start + 1, (current - start) - 1);
    addToken(STRING, s);
}

/**
 * Scans the next token from the source code.
 * Identifies symbols, keywords, and literals.
 */
void Scanner::scanToken() {
    char c = source.at(current++);
    switch (c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
    case '!':
        addToken(match('=') ? BANG_EQUAL : BANG);
        break;
    case '=':
        addToken(match('=') ? EQUAL_EQUAL : EQUAL);
        break;
    case '<':
        addToken(match('=') ? LESS_EQUAL : LESS);
        break;
    case '>':
        addToken(match('=') ? GREATER_EQUAL : GREATER);
        break;
    case '/':
        if (match('/')) {
            while (!isEnd() && source.at(current) != '\n') {
                current += 1;
            }
        }
        else
            addToken(SLASH);
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case '"':
        stringCase();
        break;

    default:
        if (isDigit(c)) {
            number();
        }
        else if(isAlpha(c)){
            identifier();
        }
        else {
            Clox::error(line, "Unexpected character.");
        }       
        break;
    }
};

//Scans the entire source code and returns a list of tokens.
list<Token> Scanner::scanTokens() {
    while (!isEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(EOD, "", nullptr, line);
    return tokens;
};

// Checks if a character is a digit.
bool Scanner::isDigit(char c) {
    if (c >= '0' && c <= '9') 
        return true;
    return false;
}

//Handles numeric literals and converts them into tokens.
void Scanner::number() {
    while (isDigit(source.at(current))) {
        current++;
    }
    if (source.at(current) == '.') {
        if (current + 1 >= source.length())
            return;
        current++;
    }
    while (isDigit(source.at(current))) {
        current++;
    }

    stringstream s(source.substr(start, current - start) );
    double num;
    s >> num;
    addToken(NUMBER , num);

};

//Checks if a character is an alphabetic letter or underscore.
bool Scanner::isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));      
}

//Checks if a character is alphanumeric (letter or digit).
bool Scanner::isAlphaNumeric(char c) {
    return (isDigit(c) || isAlpha(c));
}

/**
 * Handles identifiers and keywords.
 * Identifies if a token is a keyword or an identifier.
 */
void Scanner::identifier() {

    while (isAlphaNumeric(source.at(current))) {
        current++;

    }
    string s = source.substr(start, (current - start));
    unordered_map<string, TokenType>::iterator p;
    p = keywords.find(s);
    TokenType type;
    if (p == keywords.end()) 
        type = IDENTIFIER;
    else
        type = p->second;
    addToken(type);
    /*TokenType type = keywords[s];
    if (type == null)
        type
    addToken(IDENTIFIER);*/
}