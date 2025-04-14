#pragma once
#include<string>
#include<any>
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

enum TokenType {
	// Single-character tokens.(0-10)
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.(11-18)
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.(19-21)
	IDENTIFIER, STRING , NUMBER,

	// Keywords.(22-37)
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	//(38)
	EOD
};

class Token {
public:
	const TokenType type;
	const string lexeme;
	const std::any literal;
	const int line;

public:
	Token(TokenType  t, string l, any lit, int lin);
	void toString();

};

