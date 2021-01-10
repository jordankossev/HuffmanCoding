#include "DecompressCommand.h"

void DecompressCommand::execute() {
	HuffmanCoder::decompress();
}

std::string DecompressCommand::stringID() {
	return "decompress";
}
