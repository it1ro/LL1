#include "Parser.hpp"
#include <iostream>
#include <string>

int main() {
    calc::TokenStream ts{std::cin};
    std::cout << "> ";

    try {
        while (true) {
            // Пропускаем пустые строки и ; перед выражением
            auto t = ts.get();
            while (t.kind == calc::Token::semicolon ||
                   t.kind == calc::Token::newline ||
                   t.kind == calc::Token::eof) {
                if (t.kind == calc::Token::eof) {
                    std::cout << "\nBye!\n";
                    return 0;
                }
                t = ts.get();
            }
            ts.putback(t);

            double result = calc::evaluate(ts);
            std::cout << "= " << result << "\n> ";
        }
    } catch (const std::exception &e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }
}
