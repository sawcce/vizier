//
// Created by sawcce on 23/01/2022.
//

#include "lexer.h"
#include <string>
#include <regex>
#include <iostream>
#include <fmt/printf.h>

namespace lexer
{
    #define TOKEN_AMOUNT 7

    enum TokenType;

    struct Token;

    /**
     * Struct used to match (and link) together the tokenType Enum
     * and their corresponding regexs.
     * \n
     * The main purpose of that is to avoid using switch statements,
     * and provide better maintainability whenever introducing new tokens in the lexer.
     * @param type The corresponding TokenType enum variant
     * @param pattern The corresponding regex pattern used to match the enum
     */
    struct TokenMatch
    {
        TokenType type;
        std::regex pattern;
    };

    std::regex  identifier("^[a-zA-Z_][a-zA-Z_0-9]+");
    std::regex  fn("^fn");
    std::regex  whitespace("^\\s+");
    std::regex  lbracket("^\\{");
    std::regex  rbracket("^\\}");
    std::regex  lparen("^\\(");
    std::regex  rparen("^\\)");

    /**
     * Stores all of the TokenMatch struct instances used in the tokenizer.
     * \n
     * The order in which they are declared does matter, as the tokenizer goes
     * through them individually and tests the patterns, from index 0 to TOKEN_AMOUNT
     * \n
     * They are only used for iterating through them and testing each pattern,
     * thus the declaration in the source and not header.
     * Any other use is not recommended and is undocumented.
     */
    TokenMatch tokens [TOKEN_AMOUNT] =  {
        TokenMatch {TokenType::FN, fn},
        TokenMatch {TokenType::LBracket, lbracket},
        TokenMatch {TokenType::RBracket, rbracket},
        TokenMatch {TokenType::LParen, lparen},
        TokenMatch {TokenType::RParen, rparen},
        TokenMatch {TokenType::Identifier, identifier},
        TokenMatch {TokenType::Whitespace, whitespace},
    };

    std::vector<Token> tokenize(std::string inputProgram)
    {
        std::vector<Token> Tokens;
        bool keepRunning = true;

        while(keepRunning) {
            for (int i = 0; i < TOKEN_AMOUNT; i++)
            {
                std::smatch match;
                auto tkMatch = tokens[i];
                bool matches = std::regex_search(inputProgram, match, tkMatch.pattern);

                fmt::print("Trying to match {} for '{}'\n", i, inputProgram.substr(0, 1));

                if(i == 3)
                {
                    fmt::print("Trying to match parenthesis for '{}'\n", inputProgram.substr(0, 1));
                }

                if(!matches)
                {
                    // If we have reached the last matchable token
                    if(i == TOKEN_AMOUNT-1)
                    {
                        keepRunning = false;
                        fmt::print("Couldn't match any tokens for '{}'\n", inputProgram);
                    }
                    continue;
                }

                //fmt::print("{}, i:{}\n", match.position(), i);

                switch (i)
                {
                    case TOKEN_AMOUNT - 1: {
                        fmt::print("Whitespace !\n");
                        break;
                    }
                    default: {
                        Tokens.push_back(
                                    Token {
                                        tkMatch.type,
                                        inputProgram.substr(0, match.length()),
                                        0,
                                        0,
                                    }
                                );
                        break;
                    }
                }

                inputProgram = inputProgram.substr(match.length(), inputProgram.length() - match.length());

                //If the string is empty (no tokens left to match), we exit the loop
                //fmt::print("Length : {}\n", inputProgram.length());
                if (inputProgram.length() == 0)
                {
                    keepRunning = false;
                }
                break;
            }
        }
        return Tokens;
    };

};