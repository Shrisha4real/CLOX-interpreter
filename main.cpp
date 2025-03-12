#include "header.h" // Include the header file containing necessary declarations.
#include "Clox.h"   // Include the Clox class which handles the execution of the Lox language.
#include "Scanner.h" // Include the Scanner class which handles tokenization.

// use ine inbuilt Debugger to compile the project
// change the cli arguments in the Properties -> Debuggeing -> Command Arguments

int main(int argc, char** argv) {
	// Initialize keyword mappings in the Scanner class.
	Scanner::initializeKeywords();

	// Check if more than one argument (excluding program name) is provided.
	if (argc > 2) {
		cout << "usage base.exe <filename>\n";
		return 64;

	}
	// If a filename is provided as an argument, execute the script from the file
	else if (argc == 2) {
		Clox::runFile(argv[1]); // Run the Lox script from the provided file.
	}
	else {
		Clox::readPrompt(); // Start REPL for interactive execution.
	}

}