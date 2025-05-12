#pragma once
#include "Token.h"
#include "Expr.h"
#include "Clox.h"
#include <vector>
#include <string>
#include <stdexcept>
//#include <errors.h>
class Parser
{
private:
	class ParseError : public std::runtime_error {
	public:
		ParseError() : std::runtime_error("Parse error") {}
	};
	ParseError* error(const Token* token, const std::string message);
	const std::vector<Token> tokens;
	int current = 0;
	bool match(const std::vector<TokenType>&types);//check if there are more recursive expressions to be solved
	Expr* comparison();// if matched , then returns the right part of the token returned from the previous()
	const Token* previous();//returns the token that links the left and the right expression 
	inline bool isEnd();
	bool check(TokenType type);
	inline const Token* advance();
	inline const Token* peek();
	
	const Token* consume(TokenType type, std::string message );
	Expr* expression();
	Expr* equality();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();
	void synchroize();

public:
	Parser(std::vector<Token> tokens) :tokens(tokens) {};
	Expr* parse();

};

