#include "CompressCommand.h"

void CompressCommand::execute() {
	HuffmanCoder::compress();
}

std::string CompressCommand::stringID() {
	return "compress";
}
