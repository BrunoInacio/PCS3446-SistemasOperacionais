
/**
 * processor.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "job.hpp"

#include <tuple>

class Processor {
public:
    Processor() : job(nullptr), isRunning(0), time(0) {};
    ~Processor() {};

    std::tuple<int, Event, int> run(Job *job, int time);
    std::tuple<int, Event, int> release(int time);

private:
    Job *job;
    bool isRunning;
    int time;
};
