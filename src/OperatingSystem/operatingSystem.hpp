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

    //static std::tuple<int, Job> stochasticJob(int maxTime);


private:
    std::unordered_map<int, Job> jobs;

    std::deque<PredictedEvent> events;
    std::deque<PredictedEvent> jobToProcess;
    std::deque<PredictedEvent> jobToMemory;
    std::deque<PredictedEvent> jobToDisk;

    std::unique_ptr<Processor> processor;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<Disk> disk;

    static const std::unordered_map<Event, void (OperatingSystem::*)(PredictedEvent)> actions;
};
