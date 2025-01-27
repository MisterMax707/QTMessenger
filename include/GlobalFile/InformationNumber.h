#pragma once
#include <string>

class InformationNumber
{
private:
    std::string allNumber;

public:
    InformationNumber() : allNumber("") {}

    InformationNumber(const std::string& str) : allNumber(str) {}

    InformationNumber operator+(const std::string& str) const
    {
        return InformationNumber(allNumber + "#" + str);
    }

    InformationNumber operator+=(const std::string& str)
    {
        allNumber += str;
        return *this;
    }
};


