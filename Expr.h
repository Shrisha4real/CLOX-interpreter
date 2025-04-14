#pragma once
#include "Token.h"
using namespace std;
#include <any> 
#include <string> 
#include <vector> 

class Expr {
public:
	virtual string accept(Visitor *visitor) = 0;
	virtual ~Expr() = default;
};

class Binary;
class Grouping;
class Literal;
class Unary;
class Visitor {
public:
	virtual std::string visitBinaryExpr(Binary* Expr) = 0;
	virtual string visitGroupingExpr(Grouping* Expr) = 0;
	virtual string visitLiteralExpr(Literal* Expr) = 0;
	virtual string visitUnaryExpr(Unary* Expr) = 0;
	virtual ~Visitor() = default;
};
class Binary : public Expr {
public:
	Expr* left;
	Token* op;
	Expr* right;
public:
	Binary(Expr* left, Token* op, Expr* right) : left(left), op(op), right(right) {};
	string accept(Visitor* visitor) override {
		return visitor->visitBinaryExpr(this);
	};
	~Binary() override = default;
};

class Grouping : public Expr {
public:
	Expr* expression;
public:
	Grouping(Expr* expression) : expression(expression) {};
	string accept(Visitor* visitor) override {
		return visitor->visitGroupingExpr(this);
	};
	~Grouping() override = default;
};

class Literal : public Expr {
public:
	any value;
public:
	Literal(any value) : value(value) {};
	string accept(Visitor* visitor) override {
		return visitor->visitLiteralExpr(this);
	};
	~Literal() override = default;
};

class Unary : public Expr {
public:
	Token* op;
	Expr* right;
public:
	Unary(Token* op, Expr* right) : op(op), right(right) {};
	string accept(Visitor* visitor) override {
		return visitor->visitUnaryExpr(this);
	};
	~Unary() override = default;
};

