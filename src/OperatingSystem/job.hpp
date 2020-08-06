/**
 * job.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"

#include <vector>

class Job {
public:
    struct Operation;
    enum class Priority;
    enum class OperationType;
    enum class State;

    Job(int totalProcessTime, int memoryUsed, Priority priority);
    ~Job() {};

    const int id;
    const int totalProcessTime;
    const int memoryUsed;

    const Priority priority;
    State state;

    void process(int duration);
    void addOperation(Operation operation);
    Operation getNextOperation();

private:
    int processedTime;
    std::vector<Operation> operations;

    static int lastId;
};

inline int Job::lastId = 0;

struct Job::Operation {
    int instant;
    OperationType operation;
    double value;
};

enum class Job::OperationType {
    IO_READ,
    IO_WRITE,
    FINISH,
};

enum class Job::State {
    SUBMIT,
    WAITING_RESOURCES,
    READY,
    RUNNING,
    WAITING_IO,
    DONE,
};

enum class Job::Priority {
    LOW,
    NORMAL,
    HIGH,
    CRITICAL,
};
