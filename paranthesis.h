#ifndef PARANTHESIS_H
#define PARANTHESIS_H
#include "op.h"

struct Paranthesis : Op {
	std::string eval() override {
		return "(" + operands[0]->eval() + ")";
	}

	std::string id() override {
		return "PARANTHESIS";
	}
};
#endif // !PARANTHESIS_H

