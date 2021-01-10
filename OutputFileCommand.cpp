#include "OutputFileCommand.h"

void OutputFileCommand::execute() {
	std::string outputFileName;
	std::cin >> outputFileName;
	HuffmanCoder::get().setOutputFileName(outputFileName);
	return;
}

std::string OutputFileCommand::stringID() {
	return "o";
}
