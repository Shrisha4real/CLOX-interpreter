#include "Clox.h"
#include "Scanner.h"
#include <fstream>
#include <sstream>

#include "AstPrinter.h"
#include "Expr.h" 
using namespace std;

static void test() {
    Expr* Binaryexpr = new Binary(new Unary(new Token(TokenType::MINUS, "-", nullptr, 1), new Literal(123)), new Token(TokenType::STAR, "*", nullptr, 1), new Grouping(new Literal(45.5)));
    AstPrinter* AST = new AstPrinter();
    std::cout<<(AST->print(Binaryexpr));

}
bool Clox::hadError = false;  

void Clox::read(const string& source) {
    Scanner* scanner = new Scanner(source);
    list<Token> tokens = scanner->scanTokens();
    cout << "size of tokens in CLOX.cpp = " << tokens.size() << endl;
    for (Token t : tokens) {
        t.toString();
    }
}

void Clox::report(int line, const string& where, const string& message) {
    cerr << "[line " << line << "] Error " + where + ": " << message << endl;
    hadError = true;
}

void Clox::error(int line, const string& message) {
    report(line, "", message);
}

void Clox::runFile(const string& filename) {
    ifstream file(filename, ios::binary);
    string line;
    if (!file) {
        cerr << "The file doesn't exist\n";
        exit(64);
    }

    ostringstream buffer;
    buffer << file.rdbuf();
    read(buffer.str());
    file.close();
    //testing ast
    test();
    if (hadError) exit(0);
}

void Clox::readPrompt() {
    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        read(line);
    }
    hadError = false;
}
