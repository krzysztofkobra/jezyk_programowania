#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <stdexcept>

Expression* parse(const std::vector<Token>& tokens) 
{
    size_t pos = 0;

    if (tokens.empty()) 
    {
        throw std::runtime_error("Error: No tokens to parse.");
    }

    try 
    {
        Expression* result = parseExpression(pos, tokens);
        if (pos == tokens.size()) 
        {
            return result;
        } 
        else 
        throw std::runtime_error("Error: Unexpected tokens after parsing.");
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

Expression* parseExpression(size_t& pos, const std::vector<Token>& tokens) 
{
    if (pos >= tokens.size()) 
    {
        throw std::runtime_error("Error: Failed to parse expression. Unexpected end of tokens at position " + std::to_string(pos) + ".");
    }

    const Token& token = tokens[pos];
    switch (token.type) 
    {
        case TokenType::NUMBER: 
        {
            ++pos;
            return new NumberExpression(token.value);
        }
        case TokenType::IDENTIFIER:
        {
            ++pos;
            return new IdentifierExpression(token.value);
        }
        case TokenType::EQUALS:
        {
            ++pos;
            Expression* left = parseExpression(pos, tokens); 
            Expression* right = parseExpression(pos, tokens); 
            return new EqualsExpression(left, right);
        }
        case TokenType::OPENPAREN:
        {
            ++pos;
            return new ParenOpenExpression();
        }
        case TokenType::CLOSEPAREN:
        {
            ++pos;
            return new ParenCloseExpression();
        }
        case TokenType::BINARYOPERATOR:
        {
            ++pos;
            std::string op = token.value;
            Expression* left = parseExpression(pos, tokens);
            Expression* right = parseExpression(pos, tokens); 
            return new BinaryOperatorExpression(op, left, right);
        }
        case TokenType::LET:
        {
            Expression* expression = parseExpression(pos, tokens);
            return parseLet(pos, tokens);
        }
        default:
            throw std::runtime_error("Error: Unexpected token type.");
    }
}

LetExpression* parseLet(size_t& pos, const std::vector<Token>& tokens)
{
    if (pos >= tokens.size()) 
    {
        throw std::runtime_error("Error: Failed to parse 'let' expression. Unexpected end of tokens at position " + std::to_string(pos) + ".");
    }

    const Token& token = tokens[pos];
    if (token.type != TokenType::LET)
    {
        throw std::runtime_error("Error: Expected 'let' keyword.");
    }

    ++pos; 

    if (pos >= tokens.size() || tokens[pos].type != TokenType::IDENTIFIER)
    {
        throw std::runtime_error("Error: Expected identifier after 'let'.");
    }

    std::string identifier = tokens[pos].value;
    ++pos;  // Przesunięcie na następny token

    if (pos >= tokens.size() || tokens[pos].type != TokenType::EQUALS)
    {
        throw std::runtime_error("Error: Expected '=' after identifier in 'let' expression.");
    }

    ++pos;  // Przesunięcie na następny token po '='
    Expression* expression = parseExpression(pos, tokens);

    return new LetExpression(identifier, expression);
}