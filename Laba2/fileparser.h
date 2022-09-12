#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "../Laba1/shared.h"
#include <fstream>

class FileParser
{
public:
    FileParser();

    inline void setFilename(std::string const& filename) {
        this->filename = filename;
    }

    void parse();

    inline RealPairs const& getParsed() const {
        return parsed;
    }

private:
    void parseImpl(std::ifstream& is);


    std::string filename;

    RealPairs parsed;
};

#endif // FILEPARSER_H
