#ifndef __OUTPUTFILE_COMMAND_H
#define __OUTPUTFILE_COMMAND_H

#include "ICommand.h"

class OutputFileCommand : public ICommand {
public:
	OutputFileCommand() {}

	void execute();
	std::string stringID();
};


#endif // !__OUTPUTFILE_COMMAND_H