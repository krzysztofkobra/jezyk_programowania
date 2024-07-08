#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType
{
    NUMBER,
    IDENTIFIER,
    EQUALS,
    OPENPAREN,
    CLOSEPAREN,
    BINARYOPERATOR,
    LET
};

struct Token
{
    TokenType type;
    std::string value;

    Token(const std::string& val, TokenType t) : value(val), type(t) {}
};

// deklaracje funkcji
void INIT_RESERVED_IDENTIFIER();

std::vector<Token> tokenize(const std::string &sourceCode);

std::vector<std::string> splitString(const std::string &sourceCode);
bool isNumber(const std::string &str);
bool isAlpha(const std::string &str);
bool isSkippable(char ch);

std::string shift(std::vector<std::string> &src);

Token token(std::string value, TokenType tokentype);

#endif