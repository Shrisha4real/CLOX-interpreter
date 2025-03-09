#include"Token.h"

Token::Token(TokenType  t, string l, any lit, int lin) : type(t), lexeme(l), literal(lit), line(lin) {

}

void Token::toString() {
		stringstream ss;
		//cout << 1<<endl;
		ss << "type = " << type << " \t lexeme= " << lexeme;
		cout << ss.str() << endl;
}