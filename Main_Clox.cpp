#include "header.h"
#include "Clox.h"
#include "Scanner.h"

// use ine inbuilt Debugger to compile the project
// change the cli arguments in the Properties -> Debuggeing -> Command Arguments

int main(int argc, char** argv) {
	std::string exePath = "E:\\C++\\tool1\\x64\\Debug\\tool1.exe E:\\C++\\dummy";
	//std::string argPath = "E:\\C++\\dummy";

	////// Wrap exePath in quotes in case it contains spaces
	//std::string command = "\"" + exePath + "\" \"" + argPath + "\"";

	//std::cout << "Running command: " << command << std::endl;

	int result = system(exePath.c_str());

	if (result == 0) {
		std::cout << "Dependent project executed successfully!" << std::endl;
	}
    else {
		std::cerr << "Execution failed!" << std::endl;
	}

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