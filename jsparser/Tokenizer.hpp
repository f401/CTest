#ifndef TOKENIZER_H
#define TOKENIZER_H 1

#include <string>
#include <vector>

namespace jsparser {

enum class Token {
	Id, Keyword,
	LeftGroup,
	RightGroup,
	LeftCurlyBraces,
	RightCurlyBraces,
	ContentEOF,
	Space, Comma,
	Plus, Minus, Mul, Divide
};

inline std::vector<std::string_view> KEYWORDS 
{"else", "if", "var", "function", "for", "while", "do"};

class Tokenizer {

public:
  typedef std::pair<Token, std::string_view> TokenResult;
  Tokenizer(const std::string_view& src);

  TokenResult nextToken();
  TokenResult forward(int count);
private:
  TokenResult __nextToken(std::string_view::iterator &pos);
  typename std::string_view::iterator curr;
  std::string_view src;
};

}; // namespace jsparser

#endif /* end of include guard: TOKENIZER_H */
