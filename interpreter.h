#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexer.h"
#include "parser.h"
#include <stdexcept>
#include <iostream>

class MathInterpreter
{
    private:
        Expression *rootExpression;

    public:
        MathInterpreter(const std::vector<Token>& tokens);
        double interpret();
        ~MathInterpreter();

    private:
        double evaluate(const Expression* expr);
};

#endif 