#pragma once

#include "Token.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace calc {

class TokenStream {
  std::istream &input_;
  std::vector<Token> buffer_;

public:
  explicit TokenStream(std::istream &in = std::cin) : input_(in) {}

  void putback(Token t) { buffer_.push_back(t); }

  Token get() {
    if (!buffer_.empty()) {
      Token t = buffer_.back();
      buffer_.pop_back();
      return t;
    }

    char ch;
    while (input_.get(ch)) {
      switch (ch) {
      case ' ':
      case '\t':
      case '\r':
        continue; // пропускаем пробелы

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':
        input_.putback(ch);
        double d;
        input_ >> d;
        return Token(d);

      case '+':
        return Token(Token::plus);
      case '-':
        return Token(Token::minus);
      case '*':
        return Token(Token::mul);
      case '/':
        return Token(Token::div);
      case '%':
        return Token(Token::mod);
      case '(':
        return Token(Token::l_par);
      case ')':
        return Token(Token::r_par);
      case ';':
        return Token(Token::semicolon);
      case '\n':
        return Token(Token::newline);

      default:
        throw std::runtime_error("Lexer error: unknown character '" +
                                 std::string(1, ch) + "'");
      }
    }

    // EOF
    return Token(Token::eof);
  }
};

} // namespace calc
