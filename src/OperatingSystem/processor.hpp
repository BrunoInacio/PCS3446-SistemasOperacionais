
/**
 * processor.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
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

    enum class Result;

    Result run(std::shared_ptr<Job> job);
    PredictedEvent getNextRelease();
    PredictedEvent release(int time);

    void info();

private:
    std::shared_ptr<Job> job;
    bool isRunning;
    int time;
};

enum class Processor::Result {
    SUCCESS,
    ERROR_CPU_UNAVAILABLE,
    ERROR_CPU_NOT_RUNNING,
    ERROR_UNRECOGNIZED_RELEASE,
};
