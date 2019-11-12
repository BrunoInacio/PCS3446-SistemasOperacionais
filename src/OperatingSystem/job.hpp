/**
 * job.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"

#include <tuple>
#include <vector>

class Job {
public:
    enum class Operation;

    Job(int totalTime, int memoryUsed, Priority priority);
    ~Job() {};

    const int id;
    const int totalTime;
    const double memoryUsed;
    const Priority priority;

    State state;

    void addOperation(std::tuple<int, Job::Operation, double>);
    void process(int duration);

    std::tuple<int, Job::Operation, double> getNextOperation();

private:
    int processedTime;
    std::vector<std::tuple<int, Job::Operation, double>> operations;

    static int lastId;
};

inline int Job::lastId = 0;

enum class Job::Operation {
    IO_READ,
    IO_WRITE,
    FINISH,
};

