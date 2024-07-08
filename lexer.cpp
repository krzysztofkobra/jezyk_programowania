#include "lexer.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

typedef std::map<std::string, TokenType> ReservedIdentMap; // upraszczanie kodu, mozliwosc uzycia 'nazwy' ReservedIdentMap
ReservedIdentMap reservedIdent; // stworzenie mapy przechowującej pary: klucz typu string - wartość typu TokenType 

void INIT_RESERVED_IDENTIFIER()
{
    reservedIdent["let"] = TokenType::LET; 
}

long long SHIFT_CURR = 0;

std::vector<Token> tokenize(const std::string &sourceCode)
{
    std::vector<Token> tokens;
    std::vector<std::string> src = splitString(sourceCode);

    while(!src.empty())
    {
        if(src.front() == "(") tokens.push_back(token(shift(src), TokenType::OPENPAREN));
        else if(src.front() == ")") tokens.push_back(token(shift(src), TokenType::CLOSEPAREN));
        else if(src.front() == "+" || src.front() == "-" || src.front() == "/" || src.front() == "*") tokens.push_back(token(shift(src), TokenType::BINARYOPERATOR));
        else if(src.front() == "=") tokens.push_back(token(shift(src), TokenType::EQUALS));
            if(isNumber(src.front()))
            {
                std::string number;
                while (!src.empty() && isNumber(src.front()))
                {
                    number += src.front();
                    shift(src);
                }
                if(!number.empty())
                {
                    tokens.push_back(token(number, TokenType::NUMBER));
                }
            }
            else if(isAlpha(src.front()))
            {
                std::string ident = shift(src);
                ReservedIdentMap::iterator it = reservedIdent.find(ident); // przeszukiwanie mapy
                if(it != reservedIdent.end()) tokens.push_back(token(ident, it->second)); // jesli znaleziono pasujacy wpis w mapie, dodaje nowy token do wektora tokens
                else tokens.push_back(token(ident, TokenType::IDENTIFIER)); // jesli nie znaleziono, dodaje token jako identyfikator
            }
            else if (isSkippable(src.front()[0])) shift(src);
            else
            {
                std::cout << "ERROR\n"; // jesli trafimy na nierozpoznawalny znak
                exit(-1); // zakonczenie programu
            }
    }
    return tokens;
}


//definicje funkcji zadeklarowanych w pliku naglowkowym
std::vector<std::string> splitString(const std::string &sourceCode)
{
    std::vector<std::string> words;
    std::string word;

    for(char ch : sourceCode)
    {
        if(ch != ' ') word += ch; // dodajemy litere do zmiennej jesli nie jest to spacja
        else if(!word.empty())
        {
            words.push_back(word); // dodajemy zmienna  do wektora
            word.clear(); // czyscimy zmienna
        }
    }

    if(!word.empty())
    {
        words.push_back(word); // główna pętla dodaje słowa tylko gdy napotka spacje, bez tej pętli nie dodamy ostatniego wyrazu do wektora
    }

    return words;
}

std::string shift(std::vector<std::string> &src) // pobiera pierwszy element z kontenera, usuwa go i zwraca zawartosc usunietego elementu
{
    std::string current = src.front();
    src.erase(src.begin());
    return current;
}

Token token(std::string value, TokenType tokentype)
{
    return {value, tokentype};
}

bool isNumber(const std::string &str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

bool isAlpha(const std::string &str)
{
    for (char ch : str)
    {
        if (!isalpha(ch))
            return false;
    }
    return true;
}
bool isSkippable(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n'; // sprawdza czy nie ma spacji, tabulacji, przejscia do nowej linii
}