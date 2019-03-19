#ifndef PROGRAM_H
#define PROGRAM_H

#include "op.h"

struct Program : Op {
	std::string eval() override {
		return operands[0]->eval();
		//return nullptr;
	}
	std::string id() override {
		return "Program";
	}
};

#endif /* PROGRAM_H */