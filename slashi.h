#ifndef SLASHI_H
#define SLASHI_H
#include "op.h"

struct Slashi :Op {
	std::string eval() override {
		return "\\I";
	}

	std::string id() override {
		return "Slashi";
	}
};
#endif // !SLASHI_H

