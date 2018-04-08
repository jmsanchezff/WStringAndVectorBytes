#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

template<typename ByteSizeType>
inline void printVectorOfBytes(const std::vector<ByteSizeType>& bytesVector)
{
    auto byteCounter = 0;
    for (auto byte : bytesVector)
    {
        std::cout << std::dec << "Byte[" << byteCounter << "] = ";
        std::cout << std::setfill('0') << std::setw(2) << std::hex << unsigned(byte) << std::endl;
        byteCounter++;
    }
}


inline void printStringCharactersAsBytes(const std::string& str)
{
    auto byteCounter = 0;
    for (auto character : str)
    {
        std::cout << std::dec << "Char[" << byteCounter << "] = ";
        std::cout << std::setfill('0') << std::setw(2) << std::hex << short(character) << std::endl;
        byteCounter++;
    }
}

inline void printStringCharactersAsBytes(const std::wstring& str)
{
    auto charCounter = 0;
    for (auto character : str)
    {
        std::cout << std::dec << "Wchar[" << charCounter << "] = ";
        std::cout << std::setfill('0') << std::setw(4) << std::hex << character << std::endl;
        charCounter++;
    }
}

