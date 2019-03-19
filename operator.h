#ifndef OPERATOR_H
#define OPERATOR_H

#include "op.h"

struct Operator : Op {
	std::string eval() override {
		return operands[0]->eval();
		//return nullptr;
	}
	std::string id() override {
		return "Operator";
	}
};

#endif /* OPERATOR_H */