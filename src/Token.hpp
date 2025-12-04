#pragma once

#include <iosfwd>
#include <string>

namespace calc {

class Token {
public:
  enum Kind {
    none = 0,
    id,
    num,
    txt,
    plus,
    minus,
    mul,
    div,
    mod,
    l_par,
    r_par,
    semicolon,
    newline,
    eos,
    eof
  };

  Kind kind = none;
  double value = 0.0;
  std::string text = "";

  Token() = default;
  explicit Token(double d) : value(d), kind(num) {}
  explicit Token(Kind k) : kind(k) {}
  explicit Token(std::string t) : text(std::move(t)), kind(txt) {}

  friend std::ostream &operator<<(std::ostream &os, const Token &t);
};

std::ostream &operator<<(std::ostream &os, const Token &t);

} // namespace calc
