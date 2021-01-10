#include "ExitCommand.h"

void ExitCommand::execute() {
	std::exit(0);
}

std::string ExitCommand::stringID() {
	return "exit";
}
