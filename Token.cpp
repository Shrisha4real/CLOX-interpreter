#include"Token.h"

/*
 * Constructor for the Token class.
 * Initializes a token with its type, lexeme, literal value, and line number.
 */
Token::Token(TokenType  t, string l, any lit, int lin) : type(t), lexeme(l), literal(lit), line(lin) {
	// Constructor initializes member variables with provided values.
}

/*
 * Converts the Token object into a string representation and prints it.
 * Displays the token type and lexeme.
 */
void Token::toString() {
		// Create a string stream to format output.
		stringstream ss;
		//cout << 1<<endl;
		ss << "type = " << type << " \t lexeme= " << lexeme; // Format token details.
		cout << ss.str() << endl;  // Print the formatted token information.
}