#pragma once

#include "TokenStream.hpp"
#include <limits>
#include <stdexcept>
#include <string>

namespace calc {

namespace detail {

double primary(TokenStream &ts);
double term(TokenStream &ts);
double expression(TokenStream &ts);

double primary(TokenStream &ts) {
  Token t = ts.get();
  switch (t.kind) {
  case Token::num:
    return t.value;
  case Token::plus:
    return +primary(ts);
  case Token::minus:
    return -primary(ts);
  case Token::l_par: {
    double val = expression(ts);
    Token next = ts.get();
    if (next.kind != Token::r_par) {
      throw std::runtime_error("Expected ')'");
    }
    return val;
  }
  case Token::eof:
    throw std::runtime_error("Unexpected end of input");
  default: {
    throw std::runtime_error("Unexpected token in primary: " +
                             std::to_string(static_cast<int>(t.kind)));
  }
  }
}

double term(TokenStream &ts) {
  double left = primary(ts);
  while (true) {
    Token t = ts.get();
    switch (t.kind) {
    case Token::mul:
      left *= primary(ts);
      break;
    case Token::div: {
      double right = primary(ts);
      if (right == 0.0) {
        return std::numeric_limits<double>::infinity();
      }
      left /= right;
      break;
    }
    case Token::mod: {
      double right = primary(ts);
      left = static_cast<int>(left) % static_cast<int>(right);
      break;
    }
    default:
      ts.putback(t);
      return left;
    }
  }
}

double expression(TokenStream &ts) {
  double left = term(ts);
  while (true) {
    Token t = ts.get();
    switch (t.kind) {
    case Token::plus:
      left += term(ts);
      break;
    case Token::minus:
      left -= term(ts);
      break;
    default:
      ts.putback(t);
      return left;
    }
  }
}

} // namespace detail

double evaluate(TokenStream &ts) { return detail::expression(ts); }

} // namespace calc
