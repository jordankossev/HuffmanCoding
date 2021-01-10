#include "HuffmanCoder.h"
#include "Invoker.h"

int main() {
	Invoker invoker;
	std::string input;
	while (true) {
		std::cin >> input;
		invoker.executeCommand(input);
	}
}

