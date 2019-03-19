#include <string>
#include <cctype>
#include <algorithm>
struct token {

	enum id {
		ID,
		DOT,
		PLUS,
		STAR,
		SLASH,
		L_PARENTHESIS,
		R_PARENTHESIS,
		L_BRACKET,
		R_BRACKET,
		END_PROGRAM
	};
	id id;
	std::string text;
};


using IT = std::string::iterator;

token next_token(const IT first, const IT last) {
	if (first == last) {
		return { token::END_PROGRAM, "" };
	}
	token tk;
	switch (*first) {
	case '+':
		tk = { token::PLUS, "+" };
		break;
	case '*':
		tk = { token::STAR, "*" };
		break;
	case '.':
		tk = { token::DOT, "." };
		break;
	case '(':
		tk = { token::L_PARENTHESIS, "(" };
		break;
	case ')':
		tk = { token::R_PARENTHESIS, ")" };
		break;
	case '{':
		tk = { token::L_BRACKET, "{" };
		break;
	case '}':
		tk = { token::R_BRACKET, "}" };
		break;
	case '\\':
		tk = { token::SLASH, "\\" };
		break;
	default:
		tk = { token::ID, std::string(first, first + 1) };
	};
	return tk;
}