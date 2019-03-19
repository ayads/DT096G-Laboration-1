#ifndef OP_H
#define OP_H
#include <iostream>
#include <string>
#include <vector>
#include "token.h"

struct Op {
	virtual std::string eval() = 0;
	virtual std::string id() = 0;
	std::vector<Op*> operands;
	//std::string source = "aloo";

	std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";

};
#endif // OP_H 