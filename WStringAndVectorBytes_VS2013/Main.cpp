#include "PrintingFunctions.h"
#include "WStringBytesManipulationTemplates.h"
#include "MemoryAccessTemplates.h"

#include <vector>
#include <iostream>
#include <iomanip>





void copyingWStringCharactersToVectorOfBytesUsingMemcpy()
{
    std::cout << "--- Copying wstring characters to std::vector of bytes using memcpy(...) ---" << std::endl;

    const int vectorSize = 16;

    std::vector<unsigned char> bytesVector(vectorSize);
    std::wstring str(L"Привет Привет Привет");
    std::wstring str2(L"\xFF00\x00FF");
    const unsigned int vectorOffset = 5;

    CopyWStringBytesToVector(str, bytesVector);
    CopyWStringBytesToVector(str2, bytesVector, vectorOffset);

    std::cout << "--- vector of bytes contains:" << std::endl;
    printVectorOfBytes(bytesVector);
    std::cout << "--- original wstring contains:" << std::endl;
    printStringCharactersAsBytes(str);
    std::cout << "--- inserted wstring at byte " << vectorOffset << std::endl;
    printStringCharactersAsBytes(str2);

    std::cin.get();
}


void copyingWStringCharactersToVectorOfBytesUsingStdCopy()
{
    std::cout << "--- Copying wstring characters to std::vector of bytes using std::copy ---" << std::endl;
    std::cout << "--- NOTE: THIS IS NOT THE WAY TO DO IT. DO NOT USE THIS APPROACH ---" << std::endl;
    std::cout << "--- This is an example to explain the reason why this is not the way to go..." << std::endl << std::endl;

    const int numOfBytesAtVector = 16;

    std::vector<unsigned char> bytesVector(numOfBytesAtVector);
    std::wstring str(L"Привет");

    std::wstring substr = str.substr(0, bytesVector.size()/sizeof(wchar_t));


    std::copy(substr.begin(), substr.end(), bytesVector.begin());

    std::cout << "--- bytes vector contains ---" << std::endl;
    printVectorOfBytes(bytesVector);

    std::cout << "--- wstring contains in values ---" << std::endl;
    printStringCharactersAsBytes(str);

    std::cout << "--- As you can see, std::copy makes a byte-by-byte copy from each wstring character (2 bytes)" << std::endl;
    std::cout << "--- to a vector element (1 byte). In the process of copying elements from the origin collection" << std::endl;
    std::cout << "--- to the target collection, std::copy copies only the less significant byte and discards the " << std::endl;
    std::cout << "--- bytes that do not fit to the size of target collection elements" << std::endl;

    std::cin.get();
}

void copyingStringCharactersToVectorOfBytesUsingStdCopy()
{
    const int numberOfBytesOfVector = 16;

    std::vector<unsigned char> bytesVector(numberOfBytesOfVector);
    std::string str("12345678901234567890");

    auto subStr = str.substr(0, bytesVector.size());

    // here we can use std::copy due to the size of the elements of vector and the elements
    std::copy(subStr.begin(), subStr.end(), bytesVector.begin());

    std::cout << "--- bytes vector contains ---" << std::endl;
    printVectorOfBytes(bytesVector);

    std::cout << "--- string contains in values ---" << std::endl;
    printStringCharactersAsBytes(str);
    std::cin.get();
}



void copyingIntegerBytesToVectorOfBytesUsingReinterpretCast()
{
    const auto numOfBytes = 16;
    std::vector<unsigned char> bytes(numOfBytes);

    // first bytes of the vector set by integer 
    int integer1 = 0xAABBCCDD;
    int integer2 = 0x11223344;

    const auto integerIndex = 2;
    const auto indexInBytes = integerIndex * sizeof(int);


    CopyBytesFromValueToMemory(integer1, bytes.data());
    CopyBytesFromValueToMemory(integer2, &bytes[indexInBytes]);


    std::cout << "--- integer 1 inserted at begining of vector contains ---" << std::endl;
    std::cout << std::hex << integer1 << std::endl;
    std::cout << "--- integer 2 inserted at byte of index " << indexInBytes << " of vector contains ---" << std::endl;
    std::cout << std::hex << integer2 << std::endl;
    std::cout << "--- bytes vector contains ---" << std::endl;
    printVectorOfBytes(bytes);

    std::cin.get();
}


void gettingWStringFromVectorOfBytes()
{
    std::wstring originalStr(L"The high-tech illusion");
    std::cout << "--- Original wstring passed to a vector of 32 bytes ---" << std::endl;
    std::wcout << originalStr << std::endl;


    // copy the wstring bytes to a vector of bytes
    const auto sizeOfVector = originalStr.size()*sizeof(wchar_t);
    std::vector<unsigned char> bytesVector(sizeOfVector);
    CopyWStringBytesToVector(originalStr, bytesVector);

    std::cout << "--- Vector of " << sizeOfVector << " bytes from which we will extract new wstring: ---" << std::endl;
    printVectorOfBytes(bytesVector);

    // get the string from bytes of contained at vector
    std::wstring wstringFromVectorBytes = GetWStringFromBytesOfVector(bytesVector, 9, 18);

    std::cout << "--- Extracted wstring from byte 9 and length of 18 bytes (9 wchars): --- " << std::endl;
    std::wcout << wstringFromVectorBytes << std::endl;
    std::cout << "-> size of wstring extracted: " << wstringFromVectorBytes.size() << std::endl;
    std::cin.get();
}

int main(int argc, char* argv[])
{
    copyingStringCharactersToVectorOfBytesUsingStdCopy();

    copyingWStringCharactersToVectorOfBytesUsingStdCopy();

    copyingWStringCharactersToVectorOfBytesUsingMemcpy();
    
    copyingIntegerBytesToVectorOfBytesUsingReinterpretCast();

    gettingWStringFromVectorOfBytes();
}

