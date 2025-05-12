#include "Parser.h"

bool Parser::match(const std::vector<TokenType> &types) {

	for (TokenType t : types) {
		if (Parser::isEnd())
			return false;

		if (tokens[current].type == t) {
			current++;
			return true;
		}
	}
	return false;	
}


Expr* Parser::expression() {
	return Parser::equality();
}

Expr* Parser::equality() {
	Expr* expr = Parser::comparison();
	
	const std::vector<TokenType> types = { TokenType::BANG_EQUAL, TokenType::EQUAL };
	while (Parser::match(types)) {
		const Token* op = Parser::previous();
		Expr* right = Parser::comparison();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

// if matched , then returns the right part of the 
// token returned from the previous()
Expr* Parser::comparison() {
	Expr* expr = Parser::term();

	const std::vector<TokenType> types = { TokenType::GREATER, TokenType::GREATER_EQUAL , TokenType::LESS, TokenType::LESS_EQUAL };
	while (Parser::match(types)) {
		const Token* op = Parser::previous();
		Expr* right = Parser::term();
		expr = new Binary(expr, op, right);
	}
	return expr;
}
Expr* Parser::term() {
	Expr* expr = Parser::factor();

	const std::vector<TokenType> types = { TokenType::MINUS, TokenType::PLUS};
	while (Parser::match(types)) {
		const Token* op = Parser::previous();
		Expr* right = Parser::factor();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::factor() {
	Expr* expr = Parser::unary();

	const std::vector<TokenType> types = { TokenType::SLASH, TokenType::STAR };
	while (Parser::match(types)) {
		const Token* op = Parser::previous();
		Expr* right = Parser::unary();
		expr = new Binary(expr, op, right);
	}
	return expr;
}


Expr* Parser::unary() {

	const std::vector<TokenType> types = { TokenType::BANG, TokenType::MINUS };
	if (Parser::match(types)) {
		const Token* op = Parser::previous();
		Expr* right = Parser::unary();
		return new Unary(op, right);
	}
	
	return Parser::primary();
}

Expr* Parser::primary() {
	if (match({ TokenType::FALSE })) {
		return new Literal(false);
	}

	if (match({ TokenType::TRUE })) {
		return new Literal(true);
	}
	if (match({ TokenType::NIL })) {
		return new Literal(nullptr);
	}

	if (match({ TokenType::NUMBER, TokenType::STRING })) {
		return new Literal(previous()->literal);
	}
	if (match({ TokenType::LEFT_PAREN })) {
		Expr* expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping(expr);
	}



	throw Parser::error(peek(), "Expect expression.");
	return nullptr;//doubt that this might work

}
const Token* Parser::previous() {
	int prev = current - 1;
	return &tokens[prev];
}

bool Parser::isEnd() {
	return (tokens[current].type == TokenType::EOD);

}
const Token* Parser::advance() {
	if (!Parser::isEnd())
		current++;
	return previous();
}
const Token* Parser::peek() {
	return &tokens[current];
}
bool Parser::check(TokenType type) {
	if (Parser::isEnd())
		return false;
	return ((Parser::peek())->type == type);
}

const Token* Parser::consume(TokenType type, std::string message) {
	if (Parser::check(type))
		return Parser::advance();
	throw Parser::error( Parser::peek(), message);
}

Parser::ParseError* Parser::error(const Token* token, const std::string message) {
	Clox::error(token, message);
	return new Parser::ParseError;
}
void Parser::synchroize() {
	current++;
	while (!Parser::isEnd()) {
		if (Parser::previous()->type == TokenType::SEMICOLON) {
			return;
		}
		switch (tokens[current].type) {
		case CLASS:
		case FUN:
		case VAR:
		case FOR:
		case IF:
		case WHILE:
		case PRINT:
		case RETURN:
			return;
		}
		current++;
	}
}
Expr* Parser::parse() {
	try {
		return Parser::expression();
	}
	catch (const ParseError* error) {
		return nullptr;
	}
}