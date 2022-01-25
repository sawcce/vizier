//
// Created by sawcce on 23/01/2022.
//

#pragma once
#include <string>
#include <variant>
#include <regex>

namespace lexer
{
    enum TokenType
    {
        FN,
        LBracket,
        RBracket,
        LParen,
        RParen,
        Identifier,
        /** This token isn't used in the final parser as it is only made to parse whitespaces which aren't pushed to the tokenizer's output*/
        Whitespace,
    };

    struct Token
    {
        TokenType type;
        std::string value;
        int start;
        int end;
    };

    std::vector<Token> tokenize(std::string inputProgram);
};