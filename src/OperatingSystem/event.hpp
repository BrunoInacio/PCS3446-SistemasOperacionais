/**
 * event.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <vector>
#include <unordered_map>

enum class Event {
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

    // System
    SYS_LOG,
};

class EventControl {
public:
    void addJobs(int num);
    void run(int time);

private:
    struct predictedEvent;
    std::vector<predictedEvent> events;

    void memAlloc();
    void memFree();

    void IOStartRead();
    void IOStartWrite();
    void IOComplete();

    void CPURun();
    void CPURelease();
    void CPUDone();

    void SysLog();

    static const std::unordered_map<Event, void (EventControl::*)()> actions;
};

inline const std::unordered_map<Event, void (EventControl::*)()> EventControl::actions = {
    { Event::MEM_ALLOC,         &EventControl::memAlloc },
    { Event::MEM_FREE,          &EventControl::memFree },

    { Event::IO_START_READ,     &EventControl::IOStartRead },
    { Event::IO_START_WRITE,    &EventControl::IOStartWrite },
    { Event::IO_COMPLETE,       &EventControl::IOComplete },

    { Event::CPU_RUN,           &EventControl::CPURun },
    { Event::CPU_RELEASE,       &EventControl::CPURelease },
    { Event::CPU_DONE,          &EventControl::CPUDone },

    { Event::SYS_LOG,           &EventControl::SysLog },
};


enum class Error {
    // Memória
    MEMORY_FULL,

    // Disco
    DISK_UNAVAILABLE,

    // Processador
    CPU_UNAVAILABLE,
};

struct predictedEvent {
    int jobID;
    double time;
    Event event;

    bool operator <(const predictedEvent e);
};
