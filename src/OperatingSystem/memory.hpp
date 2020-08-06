/**
 * memory.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <unordered_map>

class Memory {
public:
    Memory(int totalSpace) : totalSpace(totalSpace), usedSpace(0) {};
    ~Memory() {};

    enum class Result;

    Result allocate(int jobID, int size);
    Result free(int jobID);

    const int totalSpace;
    void info();

private:
    int usedSpace;
    std::unordered_map<int, int> content;
};

enum class Memory::Result {
    SUCCESS,
    ERROR_MEMORY_FULL,
};
