/**
 * memory.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <unordered_map>

class Memory {
public:
    Memory(int totalSpace) : totalSpace(totalSpace), usedSpace(0) {};
    ~Memory() {};

    const int totalSpace;

    void allocate(int id, int size);
    void free(int id);

    void info();
    std::unordered_map<int, int> getInfo() const;

private:
    int usedSpace;
    std::unordered_map<int, int> mem;
};
