#include "fileparser.h"

FileParser::FileParser()
{

}

void FileParser::parse()
{
    auto is = std::ifstream(filename);
    if(!is.is_open())
        throw std::runtime_error("Error of opening file!");

    parseImpl(is);

    is.close();
}

void FileParser::parseImpl(std::ifstream& is)
{
    parsed.clear();

    Real x, y;
    while (!is.eof()) {
        is >> x >> y;
        parsed.push_back({x, y});
    }
}
