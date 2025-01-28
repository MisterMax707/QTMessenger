#pragma once
#include "../include/QtCore/qstring.h"

class InformationNumber
{
private:
    QString allNumber;

public:
    InformationNumber() : allNumber("") {}

    InformationNumber(const QString& str) : allNumber("#" + str) {}

    InformationNumber operator=(const QString& str)
    {
        allNumber = "#" + str;
        return *this;
    }

    InformationNumber operator+(const QString& str) const
    {
        return InformationNumber(allNumber + "#" + str);
    }

    InformationNumber operator+=(const QString& str)
    {
        allNumber = allNumber + "#" + str;
        return *this;
    }

    template<typename... Args>
    InformationNumber operator+(Args... args) const
    {
        return (*this + ... + args);
    }

    QString getAllNumber() const
    {
        return allNumber;
    }
};

// Перегрузка оператора + для QString и InformationWord
InformationNumber operator+(const QString& str, const InformationNumber& infoNumber)
{
    return InformationNumber("#" + str + "#" + infoNumber.getAllNumber());
}

// Перегрузка оператора + для InformationWord и QString
InformationNumber operator+(const InformationNumber& infoNumber, const QString& str)
{
    return InformationNumber("#" + infoNumber.getAllNumber() + "#" + str);
}

// Перегрузка оператора + для двух InformationWord
InformationNumber operator+(const InformationNumber& infoNumber1, const InformationNumber& infoNumber2)
{
    return InformationNumber("#" + infoNumber1.getAllNumber() + "#" + infoNumber2.getAllNumber());
}

