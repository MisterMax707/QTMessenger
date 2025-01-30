#pragma once
#include <optional>
#include "../include/QtCore/qstring.h"
#include "../include/QtCore/qstringlist.h"
#include "../include/QtCore/qdatastream.h"

class InformationNumber;
using OptInfoNum = std::optional<InformationNumber>;

class InformationNumber
{
private:
    QString allNumber;

public:
    InformationNumber() : allNumber("") {}

    InformationNumber(const QString& str) : allNumber(str) 
    {
        if (allNumber.isEmpty() || allNumber[0] != '#')
        {
            allNumber = "#" + allNumber;
        }
    }

    template<typename Container>
    InformationNumber(const Container& containerStr) : allNumber("")
    {
        for (const auto& lstr : containerStr)
        {
            allNumber += "#" + lstr;
        }
    }

    InformationNumber operator=(const QString& str)
    {
        allNumber = "#" + str;
        return *this;
    }

    template<typename Container>
    InformationNumber operator=(const Container& containerStr)
    {
        allNumber.clear();
        for (const auto& lstr : containerStr)
        {
            allNumber += "#" + lstr;
        }
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

    template<template<typename ...> class Container, typename T>
    Container<T> createArrayNumber()
    {
        Container<T> result;
        QStringList tempWords = allNumber.split('#', Qt::SkipEmptyParts);
        for (const QString& word : tempWords)
            result.insert(tempWords.end(), word);
        return result;
    }

    QString getAllNumber() const
    {
        return allNumber;
    }
};

InformationNumber operator+(const QString& str, const InformationNumber& infoNumber)
{
    return InformationNumber("#" + str + "#" + infoNumber.getAllNumber());
}

InformationNumber operator+(const InformationNumber& infoNumber, const QString& str)
{
    return InformationNumber("#" + infoNumber.getAllNumber() + "#" + str);
}

InformationNumber operator+(const InformationNumber& infoNumber1, const InformationNumber& infoNumber2)
{
    return InformationNumber("#" + infoNumber1.getAllNumber() + "#" + infoNumber2.getAllNumber());
}

QDataStream& operator<<(QDataStream& out, const InformationNumber& infoWord)
{
    out << infoWord.getAllNumber();
    return out;
}


// потоки ввода и ввывода (серилизация и десерилизация)
QDataStream& operator>>(QDataStream& in, InformationNumber infoWord)
{
    QString allNumber;
    in >> allNumber;
    infoWord = InformationNumber(allNumber);
    return in;
}

QDataStream& operator<<(QDataStream& out, const std::optional<InformationNumber>& value)
{
    if (value.has_value()) {
        out << true;
        out << value.value();
    }
    else {
        out << false;
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, std::optional<InformationNumber>& value) {
    bool hasValue;
    in >> hasValue;
    if (hasValue) {
        InformationNumber infoNumber;
        in >> infoNumber;
        value = infoNumber;
    }
    else {
        value = std::nullopt;
    }
    return in;
}