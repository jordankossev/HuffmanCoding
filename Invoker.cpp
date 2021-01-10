#include "Invoker.h"

Invoker::Invoker() {
	commands.push_back(new InputFileCommand());
	commands.push_back(new OutputFileCommand());
	commands.push_back(new CompressCommand());
	commands.push_back(new DecompressCommand());
	commands.push_back(new DebugCommand());
	commands.push_back(new ExitCommand());
}

Invoker::~Invoker() {
	for (size_t i = 0; i < commands.size(); i++) {
		delete commands[i];
	}
}

void Invoker::executeCommand(const std::string& input) {
	for (size_t i = 0; i < commands.size(); i++) {
		if (commands[i]->stringID() == input) {
			commands[i]->execute();
		}
	}
}
