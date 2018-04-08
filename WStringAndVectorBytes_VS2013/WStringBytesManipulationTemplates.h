#pragma once
#include <string>
#include <vector>
#include <memory>
#include <codecvt>


template<typename VectorElementsType>
void CopyWStringBytesToVector(const std::wstring& originString, std::vector<VectorElementsType>& targetVector, unsigned int vectorOffset = 0)
{
    auto maxNumOfWChars = (targetVector.size() - vectorOffset)*sizeof(VectorElementsType) / sizeof(wchar_t);
    std::wstring adaptedString = originString.substr(0, maxNumOfWChars);
    const auto numBytesToCopy = adaptedString.size() * sizeof(wchar_t);
    memcpy(&targetVector[vectorOffset], adaptedString.data(), numBytesToCopy);
}


template<typename VectorElementsType>
std::wstring GetWStringFromBytesOfVector(const std::vector<VectorElementsType>& originVector, unsigned int fromIndex = 0, unsigned int numberElementsToCopy = 0)
{
    auto vectorSize = originVector.size();

    if (fromIndex >= vectorSize || fromIndex + numberElementsToCopy>vectorSize)
        throw std::runtime_error("Index out of limits of the vector");

    if (numberElementsToCopy==0)
        numberElementsToCopy = vectorSize - fromIndex;

    const auto wcharsOfVector = reinterpret_cast<const wchar_t*>(originVector.data());

    const auto fromIndexInWChars = fromIndex / sizeof(wchar_t);
    const auto numOfCharsToCopy = numberElementsToCopy / sizeof(wchar_t);

    return std::wstring(wcharsOfVector + fromIndexInWChars, numOfCharsToCopy);
}
