#ifndef __INVOKER_H
#define __INVOKER_H

#include <vector>

#include "ICommand.h"
#include "InputFileCommand.h"
#include "OutputFileCommand.h"
#include "CompressCommand.h"
#include "DecompressCommand.h"
#include "DebugCommand.h"
#include "ExitCommand.h"

class Invoker {
private:
	std::vector<ICommand*> commands;
public:
	Invoker();
	~Invoker();

	void executeCommand(const std::string&);
};


#endif // !__INVOKER_H