#ifndef DOT_H
#define DOT_H
#include "op.h"

struct Dot :Op {
	std::string eval() override {
		return ".";
	}

	std::string id() override {
		return "Dot";
	}
};
#endif // !DOT_H

