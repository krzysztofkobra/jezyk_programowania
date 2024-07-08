#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <cassert>
#include <vector>

// g++ main.cpp lexer.cpp -o program, ./program

void Tokenizer(std::string src);
std::string getTokenTypeName(TokenType type);

int main()
{
    INIT_RESERVED_IDENTIFIER();

    std::string sourceCode = "(42 + 3)";
    std::vector<Token> tokens = tokenize(sourceCode);

    std::cout << "Tokens: " << std::endl;
    for (const auto& token : tokens)
    {
        std::string tokenTypeName = getTokenTypeName(token.type); 
        std::cout << tokenTypeName << "(" << token.value << ")" << std::endl;
    }

    //Tokenizer("let x = 42 + 3");
    std::string getTokenTypeName(TokenType type);

    Expression* expression = parse(tokens);
    MathInterpreter interpreter(tokens);
    double result = interpreter.interpret();
    std::cout << "Result: " << result << std::endl;

    return 0;
}

void Tokenizer(std::string sourceCode)
{
    std::vector<Token> tokens = tokenize(sourceCode);

    std::cout << "Tokens: " << std::endl;
    for (const auto& token : tokens)
    {
        std::string tokenTypeName = getTokenTypeName(token.type); 
        std::cout << tokenTypeName << "(" << token.value << ")" << std::endl;
    }
}

std::string getTokenTypeName(TokenType type)
{
    switch(type)
    {
        case TokenType::OPENPAREN: return "OPENPAREN";
        case TokenType::CLOSEPAREN: return "CLOSEPAREN";
        case TokenType::BINARYOPERATOR: return "BINARYOPERATOR";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::LET: return "LET";
        default: return "UNKNOWN";
    }
}
