/**
 * operatingSystem.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "job.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "disk.hpp"

#include <memory>
#include <deque>
#include <unordered_map>

class OperatingSystem {
public:
    OperatingSystem();
    OperatingSystem(OperatingSystem& OS) {};
    ~OperatingSystem() {};

    void addProcessor(Processor &&p);
    void addMemory(Memory &&m);
    void addDisk(Disk &&d);

    void info();
    void infoHardware();

    PredictedEvent addJob(Job &&j);

    PredictedEvent memAlloc(int jobID);
    PredictedEvent process(int jobID);

    std::unordered_map<int, std::shared_ptr<Job>> jobs;

private:
    int time;

    void waitProcessor(int jobID);
    void waitMemory(int jobID);
    void waitDisk(int jobID);

    std::deque<int> jobToProcess;
    std::deque<int> jobToMemory;
    std::deque<int> jobToDisk;

    std::unique_ptr<Processor> processor;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<Disk> disk;
};
