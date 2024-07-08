#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class Expression 
{
public:
    virtual ~Expression() = default;
};

class NumberExpression : public Expression 
{
public:
    std::string value;
    NumberExpression(const std::string& val) : value(val) {}
};

class IdentifierExpression : public Expression 
{
public:
    std::string name;

    IdentifierExpression(const std::string& name) : name(name) {}
};

class EqualsExpression : public Expression 
{
public:
    Expression* left;
    Expression* right;

    EqualsExpression(Expression* left, Expression* right) : left(left), right(right) {} // mozna zrobic to na wskaznikach z biblioteki memory aby usprawnic kod
    virtual ~EqualsExpression() 
    {
        delete left;
        delete right;
    }
};

class ParenOpenExpression : public Expression 
{
public:
    ParenOpenExpression() {}
};

class ParenCloseExpression : public Expression
{
public:
    ParenCloseExpression() {}
};

class BinaryOperatorExpression : public Expression 
{
public:
    std::string op;
    Expression* left;
    Expression* right;

    BinaryOperatorExpression(const std::string& op, Expression* left, Expression* right) : op(op), left(left), right(right) {}
    virtual ~BinaryOperatorExpression() 
    {
        delete left;
        delete right;
    }
};

class LetExpression : public Expression 
{
public:
    std::string identifier;
    Expression* expression;

    LetExpression(const std::string& identifier, Expression* expression) : identifier(identifier), expression(expression) {}
    virtual ~LetExpression() {
        delete expression;
    }
};

Expression* parse(const std::vector<Token>& tokens);
Expression* parseExpression(size_t& pos, const std::vector<Token>& tokens);
LetExpression* parseLet(size_t& pos, const std::vector<Token>& tokens);

#endif 