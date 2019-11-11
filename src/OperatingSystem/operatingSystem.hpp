/**
 * operatingSystem.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <memory>

#include "processor.hpp"
#include "memory.hpp"
#include "disk.hpp"
#include "job.hpp"

class OperatingSystem {
public:
    OperatingSystem();
    ~OperatingSystem() {};

    void addStochasticJobs(int num);
    void addProcessor(Processor &&p);
    void addMemory(Memory &&m);
    void addDisk(Disk &&d);

    void info();
    void infoJobs();

private:
    std::unordered_map<int, Job> jobs;

    std::unique_ptr<Processor> processor;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<Disk> disk;
};
