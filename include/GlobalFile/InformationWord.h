#pragma once
#include <optional>
#include "../include/QtCore/qstring.h"
#include "../include/QtCore/qstringlist.h"
#include "../include/QtCore/qdatastream.h"

class InformationWord;
using OptInfoWord = std::optional<InformationWord>;

class InformationWord
{
private:
    QString allWord;

public:
    InformationWord() : allWord("") {}

    InformationWord(const QString& str)
    {
        if (allWord.isEmpty())
        {
            allWord = "|" + str;
        }
    }

    template<typename Container>
    InformationWord(const Container& containerStr) : allWord("")
    {
        for (const auto& lstr : containerStr)
        {
            allWord += "|" + lstr;
        }
    }

    InformationWord operator=(const QString& str)
    {
        allWord = "|" + str;
        return *this;
    }

    template<typename Container>
    InformationWord operator=(const Container& containerStr)
    {
        allWord.clear();
        for (const auto& lstr : containerStr)
        {
            allWord += "|" + lstr;
        }
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

    template<template<typename ...> class Container, typename T>
    Container<T> createArrayWord()
    {
        Container<T> result;
        QStringList tempWords = allWord.split('|', Qt::SkipEmptyParts);
        for (const QString& word : tempWords)
            result.append(word);
        return result;
    }

    QString getAllWord() const
    {
        return allWord;
    }
};

//inline InformationWord operator+(const QString& str, const InformationWord& infoWord)
//{
//    return InformationWord(str + "|" + infoWord.getAllWord());
//}
//
//inline InformationWord operator+(const InformationWord& infoWord, const QString& str)
//{
//    return InformationWord(infoWord.getAllWord() + "|" + str);
//}
//
//inline InformationWord operator+(const InformationWord& infoWord1, const InformationWord& infoWord2)
//{
//    return InformationWord(infoWord1.getAllWord() + infoWord2.getAllWord());
//}


// потоки ввода и ввывода (серилизация и десерилизация)
inline QDataStream& operator<<(QDataStream& out, const InformationWord& infoWord)
{
    out << infoWord.getAllWord();
    return out;
}

inline QDataStream& operator>>(QDataStream& in, InformationWord& infoWord)
{
    QString allWord;
    in >> allWord;
    infoWord = InformationWord(allWord);
    return in;
}

inline QDataStream& operator<<(QDataStream& out, const std::optional<InformationWord>& value)
{
    if (value.has_value()) {
        out << true;
        out << value.value();
    }
    else {
        out << false;
        out << InformationWord("nan");
    }
    return out;
}

inline QDataStream& operator>>(QDataStream& in, std::optional<InformationWord>& value) {
    bool hasValue;
    in >> hasValue;
    if (hasValue) {
        InformationWord infoWord;
        in >> infoWord;
        value = infoWord;
    }
    else {
        value = InformationWord("nan");
    }
    return in;
}

namespace space
{
    namespace
    {
        inline QString concatenate(const QString& str1, const QString& str2)
        {
            return str1 + "|" + str2;
        }

        // Шаблонная функция для обработки переменного количества аргументов
        template<typename... Args>
        inline QString concatenate(const QString& first, const QString& second, Args... args)
        {
            return concatenate(first + "|" + second, args...);
        }
    }

    template<typename... Args>
    inline InformationWord combine(const QString& first, const QString& second, Args... args)
    {
        return Info(concatenate(first, second, args...));
    }

    // Специализация для двух аргументов
    inline InformationWord combine(const QString& first, const QString& second)
    {
        return InformationWord(concatenate(first, second));
    }
}