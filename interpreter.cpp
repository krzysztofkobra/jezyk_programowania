#include <iostream>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

    MathInterpreter::MathInterpreter(const std::vector<Token>& tokens)
    {
        size_t pos = 0;
        rootExpression = parseExpression(pos, tokens);
    }

    double MathInterpreter::interpret()
    {
        return evaluate(rootExpression);
    }

    MathInterpreter::~MathInterpreter()
    {
        delete rootExpression;
    }
    double MathInterpreter::evaluate(const Expression* expr) 
    {
        if (const NumberExpression* ne = dynamic_cast<const NumberExpression*>(expr)) 
        {
            return std::stod(ne->value);
        } 
        else if (const BinaryOperatorExpression* boe = dynamic_cast<const BinaryOperatorExpression*>(expr)) 
        {
            double left = evaluate(boe->left);
            double right = evaluate(boe->right);
            if (boe->op == "+") return left + right;
            else if (boe->op == "-") return left - right;
            else if (boe->op == "*") return left * right;
            else if (boe->op == "/") return left / right;
            else throw std::runtime_error("Unknown operator: " + boe->op);
        }
            else throw std::runtime_error("Unsupported expression type");
    }

