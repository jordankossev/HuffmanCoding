#include "InputFileCommand.h"

void InputFileCommand::execute() {
	std::string inputFileName;
	std::cin >> inputFileName;
	HuffmanCoder::get().setInputFileName(inputFileName);
	return;
}

std::string InputFileCommand::stringID() {
	return "i";
}
