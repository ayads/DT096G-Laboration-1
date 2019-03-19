#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "op.h"

struct Characters : Op {
	std::string _id;
	std::string eval() override {
		return _id;
	}
	std::string id() override {
		return "Characters";
	}
};

#endif // !CHARACTER_H