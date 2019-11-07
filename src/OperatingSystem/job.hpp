/**
 * job.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <tuple>
#include <vector>

class Job {
public:
    enum class Operation;
    enum class Priority;
    enum class State;

    Job(int totalTime, double memoryUsed, Job::Priority priority);
    ~Job() {};

    const int id;
    const int totalTime;
    const double memoryUsed;
    const Job::Priority priority;

    Job::State state;

    void addOperation(std::tuple<int, Job::Operation, double>);
    void process(int duration);

    std::tuple<Job::Operation, int> getNextOperation();

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

enum class Job::Priority {
    LOW,
    NORMAL,
    HIGH,
    CRITICAL,
};

enum class Job::State {
    SUBMIT,
    WAITING_RESOURCES,
    READY,
    RUNNING,
    WAITING_IO,
    DONE,
};
