#pragma once

template<typename ValueType>
void CopyBytesFromValueToMemory(const ValueType& value, void* targetMemoryPtr)
{
    auto pointerToValue = reinterpret_cast<ValueType *>(targetMemoryPtr);
    *pointerToValue = value;
}