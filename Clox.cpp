#include "Clox.h"      // Include the Clox class header.
#include "Scanner.h"   // Include the Scanner class for tokenizing input.
#include <fstream>     // Include file stream for reading files.
#include <sstream>     // Include string stream for handling input buffers.
using namespace std;

// Static variable to track whether an error has occurred during execution.
bool Clox::hadError = false;  

// Reads and processes the given source code.
void Clox::read(const string& source) {
    Scanner* scanner = new Scanner(source); // Create a Scanner instance for tokenizing input.
    list<Token> tokens = scanner->scanTokens(); // Scan the input and retrieve the list of tokens.
    cout << "size of tokens in CLOX.cpp = " << tokens.size() << endl;
    for (Token t : tokens) {
        t.toString();
    }
}

//  Reports an error encountered during execution.
void Clox::report(int line, const string& where, const string& message) {
    cerr << "[line " << line << "] Error " + where + ": " << message << endl;
    hadError = true; // Set error flag to true.
}

// Reports a generic error without specifying a location.
void Clox::error(int line, const string& message) {
    report(line, "", message);
}

// Reads and executes a Lox script from a file.
void Clox::runFile(const string& filename) {
    ifstream file(filename, ios::binary);
    string line;
    if (!file) { // Check if the file exists and is accessible.
        cerr << "The file doesn't exist\n";
        exit(64); // exit code with error 64
    }

    ostringstream buffer;
    buffer << file.rdbuf(); // Read the entire file into a buffer.
    read(buffer.str()); // Process the file contents.
    file.close();

    if (hadError) exit(0); // Exit if an error was encountered during execution.
}

// Starts an interactive prompt (REPL) for executing Lox commands.
void Clox::readPrompt() {
    string line;
    while (true) {
        cout << "> "; // Display prompt symbol.
        if (!getline(cin, line)) break; // Read input from the user; exit if no input is provided
        read(line); // Read input from the user; exit if no input is provided
    }
    hadError = false; // Read input from the user; exit if no input is provided
}
