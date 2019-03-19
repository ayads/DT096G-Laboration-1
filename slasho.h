#ifndef SLASHO_H
#define SLASHO_H
#include "op.h"

struct Slasho :Op {
	std::string _id;
	std::string eval() override {
		return "\\O{" + _id + "}";
	}

	std::string id() override {
		return "Slasho";

	}
};
#endif // !SLASHO_H

