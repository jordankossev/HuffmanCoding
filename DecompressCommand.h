#ifndef __DECOMPRESS_COMMAND_H
#define __DECOMPRESS_COMMAND_H

#include "ICommand.h"

class DecompressCommand : public ICommand {
public:
	void execute();
	std::string stringID();
};

#endif // !__DECOMPRESS_COMMAND_H