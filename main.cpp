#include "op.h"
#include "program.h"
#include "regexp.h"
#include "characters.h"
#include "add.h"
#include "star.h"
#include "dot.h"
#include "paranthesis.h"
#include "brackets.h"
#include "slashi.h"
#include "slasho.h"
#include "operator.h"
#include "seperator.h"



Op *getParseTree(IT first, IT last);
Op *getRegExp(IT first, IT last);
Op *getSeperators(IT &first, IT last);
Op *getOperators(IT &first, IT last);
Op *getCharacters(IT &first, IT last);


Op *getSeperators(IT &first, IT last) {
	token tk = next_token(first, last);
	Seperator *sep = new Seperator;

	if (tk.id == token::L_BRACKET) {
		Brackets *bracketExpr = new Brackets;
		first++;
		tk = next_token(first, last);
		while (tk.id == token::ID){
			bracketExpr->_id += tk.text;
			tk = next_token(++first, last);
		}
		first++;
		sep->operands.push_back(bracketExpr);
		return sep;
	}
	else if (tk.id == token::L_PARENTHESIS) {
		Paranthesis *par = new  Paranthesis;
		tk = next_token(++first, last);
		std::string RE = "";
		while (tk.id != token::R_PARENTHESIS)
		{
			RE += tk.text;
			tk = next_token(++first, last);
		}
		Op *regExp = getRegExp(RE.begin(), RE.end());
		
		if (tk.id == token::R_PARENTHESIS) {
			first++;
		}
		if (regExp) {
			par->operands.push_back(regExp);
			sep->operands.push_back(par);
			return sep;
		}
	}
	else if (tk.id == token::SLASH){
		IT start = first;
		first++;
		if (*(first) == 'O') {
			Slasho *so = new Slasho;
			first++;
			first++;
			tk = next_token(first, last);
			while (tk.id == token::ID) {
				so->_id += tk.text;
				tk = next_token(++first, last);
			}
			first++;
			sep->operands.push_back(so);
			return sep;
		}
		else if (*(first) == 'I') {
			Slashi *si = new Slashi;
			first++;
			sep->operands.push_back(si);
			return sep;
		}
	}
	else
	{
		return nullptr;

	}

}

Op *getOperators(IT &first, IT last) {
	token tk = next_token(first, last);
	Operator *op = new Operator;
	switch (tk.id) {
	//DOT
	case 1: {
		Dot *expr = new Dot;
		op->operands.push_back(expr);
		first++;
		return op; }
	//PLUS
	case 2: {
		Add *expr = new Add;
		op->operands.push_back(expr);
		first++;
		return op; }
	//STAR
	case 3: {
		Star *expr = new Star;
		op->operands.push_back(expr);
		first++;
		return op; }
	
	default:
		return nullptr;
	}
}

Op *getCharacters(IT &first, IT last) {
	token tk = next_token(first, last);
	if (tk.id != token::ID) { 
		return nullptr; 
	}
	Characters *expr = new Characters;
	while (first != last && tk.id == token::ID)
	{
		expr->_id += tk.text;
		tk = next_token(++first, last);
	}

	return expr;
}



Op* getRegExp(IT first, IT last) { 
	
	if (first == last) {
		return nullptr;
	}
	Op *characters = getCharacters(first, last);
	Regexp *expr = new Regexp;
	if (!characters) {
		Op *operators = getOperators(first, last);
		if (!operators) {
			Op *seperators = getSeperators(first, last);
			if (!seperators) {
				return nullptr;
			}
			else{
				expr->operands.push_back(seperators);

			}
		}
		else{
			expr->operands.push_back(operators);
		}
	}
	else{
		expr->operands.push_back(characters);
	}
	if (first != last) {
		expr->operands.push_back(getRegExp(first, last));
	}

		return expr;
}

Op *getParseTree(IT first, IT last) {
	if (first == last) {
		return nullptr;
	}
	Op *regExp = getRegExp(first, last);
	Program *expr = new Program;
	expr->operands.push_back(regExp);
	return expr;
}

std::string adder(std::string lhs, Op *abstractSyntaxtTree) {
	std::string result = "";
	std::string src = abstractSyntaxtTree->source;
	if (abstractSyntaxtTree->operands[1]->operands[0]->id() == "Characters") {
		std::string rhs = abstractSyntaxtTree->operands[1]->operands[0]->eval();
		if (src.find(lhs) != std::string::npos) {
			result += lhs;
		}
		if (src.find(rhs) != std::string::npos) {
			result += rhs;
		}
	}
	return result;
};

std::string starer(std::string lhs, Op *abstractSyntaxtTree) {
	std::string result = "";
	std::vector<std::string> match;
	std::string src = abstractSyntaxtTree->source;
	IT first = src.begin();
	IT last = src.end();
	IT nx = std::next(first, 1);
	while (first != last){
		std::string temp;
		for (int i = 0; first != last && lhs[i] == *first; i++) {
			temp += *first;
			nx = std::next(first, 1);
			first++;
			while (lhs[i] == *(nx) && first != last){
				temp += *first;
				nx = first++;
			} 
		}
		if (first != last) {
			first++;
		}
		if (!temp.empty()) {
			match.push_back(temp);
		}
	}
	result = match.at(0);
	return result;
}

std::string doter(std::string lhs, Op *abstractSyntaxtTree) {
	std::string result = "";
	std::vector<std::string> match;
	std::string src = abstractSyntaxtTree->source;
	IT first = src.begin();
	IT last = src.end();
	IT nx = std::next(first, 1);
	std::size_t wordBeginPosition = src.find(lhs);
	std::size_t charactersToInclude = (lhs.size() + 1);
	while (wordBeginPosition != std::string::npos) {
		std::string temp;
		temp= src.substr(wordBeginPosition, charactersToInclude);
		if (wordBeginPosition <= src.size()) {
			wordBeginPosition = src.find(lhs, wordBeginPosition + 1);
		}
		match.push_back(temp);
	}
	result = match.at(0);
	return result;
}


void treeAnalyser(Op *tree) {
	std::string result = "";
	std::string lhs;
	std::string src = tree->source;
	auto treeReader = tree->operands[0];
	while (treeReader != nullptr) {
		//Characters
		if (treeReader->operands[0]->id()=="Characters") {
			lhs = treeReader->operands[0]->eval();
		}
		//Seperators
		else if(treeReader->operands[0]->id() == "Operator")
		{
			if (treeReader->operands[0]->operands[0]->id() == "Add") {
				result += adder(lhs, treeReader);
			}
			else if (treeReader->operands[0]->operands[0]->id() == "Star") {
				result += starer(lhs, treeReader);
			}
			else if (treeReader->operands[0]->operands[0]->id() == "Dot") {
				result += doter(lhs, treeReader);
			}
		}
		//Seperators
		else if (treeReader->operands[0]->id() == "Seperator") {

			if (treeReader->operands[0]->operands[0]->id() == "") {
				result += adder(lhs, treeReader);
			}
			else if (treeReader->operands[0]->operands[0]->id() == "") {
				result += starer(lhs, treeReader);
			}
			else if (treeReader->operands[0]->operands[0]->id() == "") {
				result += doter(lhs, treeReader);
			}


		}
		if ((treeReader->operands.size() > 1)) {
			treeReader = treeReader->operands[1];
		}
		else {
			break;
		}
	}
	std::cout << result;
}

int main() {
	std::string match = "lov.";

	Op *result = getParseTree(match.begin(), match.end());
	treeAnalyser(result);
	std::cin.get();
	return 0;
}

//return EXIT_SUCCESS //  return EXIT_FAILURE