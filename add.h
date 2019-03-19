#ifndef ADD_H
#define ADD_H
#include "op.h"

struct Add :Op {
	std::string eval() override {
		return "+";
	}

	std::string id() override {
		return "Add";
	}
};
#endif // !ADD_H

