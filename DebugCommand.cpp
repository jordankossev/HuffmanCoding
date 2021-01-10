#include "DebugCommand.h"

void DebugCommand::execute() {
	HuffmanCoder::debug();
}

std::string DebugCommand::stringID() {
	return "debug";
}
