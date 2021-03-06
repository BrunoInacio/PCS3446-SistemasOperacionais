/**
 * memory.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brand�o In�cio
 */

#pragma once

#include <unordered_map>

class Memory {
public:
    Memory(int totalSpace) : totalSpace(totalSpace), usedSpace(0) {};
    ~Memory() {};

    const int totalSpace;

    void allocate(int jobID, int size);
    void free(int jobID);

    void info();
    std::unordered_map<int, int> getInfo() const;

private:
    int usedSpace;
    std::unordered_map<int, int> mem;
};
