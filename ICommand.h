#ifndef __ICOMMAND_H
#define __ICOMMAND_H

#include "HuffmanCoder.h"

class ICommand {
public:
	virtual void execute() = 0;
	virtual std::string stringID() = 0;
};

#endif // !__ICOMMAND_H