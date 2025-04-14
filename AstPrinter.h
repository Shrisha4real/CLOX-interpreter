#pragma once
#include "Expr.h"
#include <vector>
#include <sstream>
class AstPrinter: public Visitor
{
public:
	std::string print(Expr *expr);
	std::string visitBinaryExpr(Binary* expr) override ;
	std::string visitGroupingExpr(Grouping* Expr)override ;
	std::string visitLiteralExpr(Literal* Expr)override ;
	std::string visitUnaryExpr(Unary* Expr) override ;
private:
	std::string parenthesis(std::string name, std::vector<Expr *> exprs);

};

