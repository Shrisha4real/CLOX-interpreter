#include "Clox.h"
#include "Scanner.h"
#include <fstream>
#include <sstream>
using namespace std;

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
