#include "Scanner.h"
#include "Clox.h"  
#include "Token.h"
#include <iostream>
#include <sstream>

using namespace std;
unordered_map<string, TokenType> Scanner::keywords;
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

Scanner::Scanner(string source) : source(source) {
    tokens.clear();
    
}

bool Scanner::isEnd() {
    return (current >= source.length());
}

void Scanner::addToken(TokenType type, any literal) {
    int dif = (current - start == 0) ? 1 : (current - start);
    string text = source.substr(start, dif);
    tokens.emplace_back(type, text, literal, line);
}

void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}

bool Scanner::match(char expect) {
    if (isEnd()) return false;
    if (source.at(current) == expect) {
        current++;
        return true;
    }
    return false;
}

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

list<Token> Scanner::scanTokens() {
    while (!isEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(EOD, "", nullptr, line);
    return tokens;
};

bool Scanner::isDigit(char c) {
    if (c >= '0' && c <= '9') 
        return true;
    return false;
}

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
bool Scanner::isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));      
}

bool Scanner::isAlphaNumeric(char c) {
    return (isDigit(c) || isAlpha(c));
}
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