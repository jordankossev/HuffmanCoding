#ifndef __INPUTFILE_COMMAND_H
#define __INPUTFILE_COMMAND_H

#include "ICommand.h"

class InputFileCommand : public ICommand {
public:
	InputFileCommand() {}

	void execute();
	std::string stringID();
};



#endif // !__INPUTFILE_COMMAND_H