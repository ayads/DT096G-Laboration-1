#ifndef BRACKETS_H
#define BRACKETS_H
#include "op.h"

struct Brackets : Op {
	std::string _id;
	int a = 5;
	std::string eval() override {
		return "{" + _id + "}";
	}

	std::string id() override {
		return "Brackets";
	}


};
#endif // !BRACKETS_H