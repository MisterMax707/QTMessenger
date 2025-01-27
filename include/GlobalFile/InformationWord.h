#pragma once
#include <string>

class InformationWord
{
private:
    std::string allWord;

public:
    InformationWord() : allWord("") {}

    InformationWord(const std::string& str) : allWord(str) {}

    InformationWord operator+(const std::string& str) const
    {
        return InformationWord(allWord + "|" + str);
    }

    InformationWord operator+=(const std::string& str)
    {
        allWord += str;
        return *this;
    }
};

