#ifndef __DEBUG_COMMAND_H
#define __DEBUG_COMMAND_H

#include "ICommand.h"

class DebugCommand : public ICommand {
public:
	void execute();
	std::string stringID();
};

#endif // !__DEBUG_COMMAND_H