#pragma once
#include "../include/QtCore/qstring.h"

class InformationWord
{
private:
    QString allWord;

public:
    InformationWord() : allWord("") {}

    InformationWord(const QString& str) : allWord("|" + str) {}

    InformationWord operator=(const QString& str)
    {
        allWord = "|" + str;
        return *this;
    }

    InformationWord operator+(const QString& str) const
    {
        return InformationWord(allWord + "|" + str);
    }

    InformationWord operator+=(const QString& str)
    {
        allWord = allWord + "|" + str;
        return *this;
    }

    template<typename... Args>
    InformationWord operator+(Args... args) const
    {
        return (*this + ... + args);
    }

    QString getAllWord() const
    {
        return allWord;
    }
};

// Перегрузка оператора + для QString и InformationWord
InformationWord operator+(const QString& str, const InformationWord& infoWord)
{
    return InformationWord("|" + str + "|" + infoWord.getAllWord());
}

// Перегрузка оператора + для InformationWord и QString
InformationWord operator+(const InformationWord& infoWord, const QString& str)
{
    return InformationWord("|" + infoWord.getAllWord() + "|" + str);
}

// Перегрузка оператора + для двух InformationWord
InformationWord operator+(const InformationWord& infoWord1, const InformationWord& infoWord2)
{
    return InformationWord("|" + infoWord1.getAllWord() + "|" + infoWord2.getAllWord());
}


