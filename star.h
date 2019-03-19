#ifndef STAR_H
#define STAR_H
#include "op.h"

struct Star :Op {
	std::string eval() override {
		return "*";
	}

	std::string id() override {
		return "Star";
	}
};
#endif // !STAR_H

