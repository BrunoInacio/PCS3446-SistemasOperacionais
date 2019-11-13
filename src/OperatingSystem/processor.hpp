
/**
 * processor.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "job.hpp"

#include <memory>
#include <tuple>

class Processor {
public:
    Processor() : job(nullptr), isRunning(0), time(0) {};
    ~Processor() {};

    PredictedEvent run(std::shared_ptr<Job> job, int time);
    PredictedEvent release(int time);

    void info();

private:
    std::shared_ptr<Job> job;
    bool isRunning;
    int time;
};
