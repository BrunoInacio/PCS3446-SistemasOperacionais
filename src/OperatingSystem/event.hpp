/**
 * event.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

enum class Event {
    NONE,

    // Memória
    MEM_ALLOC,
    MEM_FREE,

    // Disco
    IO_START_READ,
    IO_START_WRITE,
    IO_COMPLETE,

    // Processor
    CPU_RUN,
    CPU_RELEASE,
    CPU_DONE,

    // Job
    JOB_ARRIVE,

    // System
    SYS_PAUSE,
};

struct PredictedEvent {
    int jobID;
    int time;
    Event event;

    double size;

    bool operator <(const PredictedEvent that) {
        return this->time < that.time;
    }
};
