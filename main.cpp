#include "header.h"
#include "Clox.h"
#include "Scanner.h"

// use ine inbuilt Debugger to compile the project
// change the cli arguments in the Properties -> Debuggeing -> Command Arguments

int main(int argc, char** argv) {
	Scanner::initializeKeywords();
	if (argc > 2) {
		cout << "usage base.exe <filename>\n";
		return 64;

	}
	else if (argc == 2) {
		Clox::runFile(argv[1]);
	}
	else {
		Clox::readPrompt();
	}

}