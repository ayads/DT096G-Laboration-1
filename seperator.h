#ifndef SEPERATOR_H
#define SEPERATOR_H

#include "op.h"

struct Seperator : Op {
	std::string eval() override {
		return operands[0]->eval();
		//return nullptr;
	}
	std::string id() override {
		return "Seperator";
	}
};

#endif /* SEPERATOR_H */