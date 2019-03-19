#ifndef REGEXP_H
#define REGEXP_H
#include "op.h"

struct Regexp:Op {
	std::string eval() override {
		if (operands.size() > 1) {
			return operands[0]->eval() + operands[1]->eval();
		}
		else {
			return operands[0]->eval();
		}
	}

	std::string id() override {
		return "Regexp";
	}
};
#endif // !REGEXP_H

