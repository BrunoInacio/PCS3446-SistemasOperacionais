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

#include <tuple>
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
    Job stochasticJob();

    PredictedEvent memAlloc(int jobID);
    PredictedEvent process(int jobID);
    PredictedEvent IO(int jobID, Disk::IO op, double size);

    std::unordered_map<int, std::shared_ptr<Job>> jobs;

    std::unique_ptr<Processor> processor;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<Disk> disk;

    PredictedEvent nextToProcessor();
    PredictedEvent nextToMemory();
    PredictedEvent nextToDisk();

    int time;

private:
    void waitProcessor(int jobID);
    void waitMemory(int jobID);
    void waitDisk(int jobID, Disk::IO op, double size);

    std::deque<std::pair<int, int>> jobToProcess;
    std::deque<std::pair<int, int>> jobToMemory;
    std::deque< std::pair<int, std::tuple<int, Disk::IO, double>>> jobToDisk;
};
