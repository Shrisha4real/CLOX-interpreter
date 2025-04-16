#include "AstPrinter.h"


std::string AstPrinter::print(Expr *expr) {
	return expr->accept(this);
}

std::string AstPrinter::visitBinaryExpr(Binary* expr) {
	std::vector<Expr*> exprs = { expr->left , expr->right };
	return AstPrinter::parenthesis((expr->op)->lexeme, exprs);
}

std::string AstPrinter::visitGroupingExpr(Grouping* expr) {
	std::vector<Expr*> exprs = { expr->expression };
	return parenthesis("group", exprs);

}
std::string AstPrinter::visitLiteralExpr(Literal* expr) {
	if (!(expr->value.has_value())) return "nil";
	if(expr->value.type()==typeid(std::string))
		return std::any_cast<std::string>(expr->value);
	else if (expr->value.type() == typeid(double)) {
		double d = std::any_cast<double>(expr->value);
		stringstream ss;
		ss << d;
		return ss.str();
	}
		

	else if (expr->value.type() == typeid(int)) {
		int i = std::any_cast<int>(expr->value);
		stringstream ss;
		ss << i;
		return ss.str();
	}

}
std::string AstPrinter::visitUnaryExpr(Unary* expr) {
	std::vector<Expr*> exprs = {expr->right};
	return parenthesis((expr->op)->lexeme, exprs);

}

std::string AstPrinter::parenthesis(std::string name, std::vector<Expr *> exprs) {
	std::stringstream ss;
	ss << "( " + name;
	for (Expr *expr : exprs) {
		ss << " ";
		ss<<  expr->accept(this);

	}
	ss << " )";
	return ss.str();
}