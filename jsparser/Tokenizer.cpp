#include "Tokenizer.hpp"
#include <iostream>
#include <algorithm>

using namespace jsparser;

static bool isSpace(char nee) {
	return nee == ' ' || nee == '\t'; 
}

static std::string readByIter(std::string_view::iterator& start) {
	std::string result;
	char curr = *start++;
	while (isalpha(curr)) {
		result.push_back(curr);
		curr = *start++;
	}
	start--;
	return result;
}

Tokenizer::Tokenizer(const std::string_view &src):  src(src) {
	this->curr = src.begin();
}

Tokenizer::TokenResult Tokenizer::forward(int count) {
	TokenResult tok;
	std::string_view::iterator myIter = curr;
	for (;count;) {
		if ((tok = __nextToken(myIter)).first == Token::ContentEOF) {
			return tok;
		}
		if (tok.first != Token::Space) {
			--count;
		}
	}
	return tok;
}

Tokenizer::TokenResult Tokenizer::nextToken() {
	TokenResult tok;
	while ((tok = this->__nextToken(curr)).first != Token::Space) {}
	return tok;
}

Tokenizer::TokenResult Tokenizer::__nextToken(std::string_view::iterator &pos) {
	char currChar = *pos;

	if (pos == src.end()) {
		return std::make_pair(Token::ContentEOF, "");
	}

	while (currChar == '\r' || currChar == '\n') {
		currChar = *++pos;
	}

	if (isSpace(currChar)) {
		++pos;
		return std::make_pair(Token::Space, " ");
	} else if (currChar == '(') {
		++pos;
		return std::make_pair(Token::LeftGroup, "(");
	} else if (currChar == ')') {
		++pos;
		return std::make_pair(Token::RightGroup, ")");;
	} else if (currChar == '{') {
		++pos;
		return std::make_pair(Token::LeftCurlyBraces, "{");
	} else if (currChar == '}') {
		++pos;
		return std::make_pair(Token::RightCurlyBraces, "}");
	} else if (currChar == ',') {
		++pos;
		return std::make_pair(Token::Comma, ",");
	} else if (currChar == '+') {
		++pos;
		return std::make_pair(Token::Plus, "+");
	} else if (currChar == '-') {
		++pos;
		return std::make_pair(Token::Minus, "-");
	} else if (currChar == '*') {
		++pos;
		return std::make_pair(Token::Mul, "*");
	} else if (currChar == '/') {
		++pos;
		return std::make_pair(Token::Divide, "/");
	}

	std::string word = readByIter(pos);
	if (std::find(KEYWORDS.cbegin(), KEYWORDS.cend(), word) != KEYWORDS.cend()) {
		return std::make_pair(Token::Keyword, word);
	}
	return std::make_pair(Token::Id, word);
}

