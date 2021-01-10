#ifndef __COMPRESS_COMMAND_H
#define __COMPRESS_COMMAND_H

#include "ICommand.h"

class CompressCommand : public ICommand {
public:
	void execute();
	std::string stringID();
};

#endif // !__COMPRESS_COMMAND_H