#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <fmt/printf.h>
#include <fmt/color.h>
#include "lexer/lexer.h"

#define VERSION "0.0.1"

std::string readFile(const char* path)
{
    std::ifstream inputFile (path);
    std::string inputString;

    if(inputFile.is_open())
    {
        std::string currentLine;
        while ( inputFile ) {
            if( inputFile.eof() ) break;

            std::getline(inputFile, currentLine);
            inputString += currentLine + "\n";
        }

        return inputString;
    } else
    {
        std::cout << "File " << path <<" is not open, exiting! \n";
        throw "File not open";
    }
}

int main()
{
    fmt::print(fg(fmt::color::yellow), "Running Vizier, version {}\n", VERSION);
    std::string inputProgram = readFile("D:\\Devlopment\\playgrounds\\cpp\\vizier\\input.vzr");
    std::cout << inputProgram;

    std::vector<lexer::Token> result = lexer::tokenize(inputProgram);

    fmt::print("Matched {} token(s)\n", result.size());

    for(const auto& token: result) {
        fmt::print(fmt::fg(fmt::color::yellow), "Token of enum index {}, {} \n", token.type, token.value);
    }

    //std::visit(visitor, result);

    return 0;
}