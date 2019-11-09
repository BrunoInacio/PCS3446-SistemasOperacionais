/**
 * eventsControl.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "operatingSystem.hpp"
#include "job.hpp"

#include <vector>
#include <unordered_map>


class EventsControl {
public:
    void addStochasticJobs(int num);
    void run(int time);
    void infoJobs();

private:
    std::unordered_map<int, Job> jobs;

    struct PredictedEvent {
        int jobID;
        double time;
        Event event;

        bool operator <(const PredictedEvent e);
    };

    std::vector<PredictedEvent> events;

    void memAlloc();
    void memFree();

    void IOStartRead();
    void IOStartWrite();
    void IOComplete();

    void CPURun();
    void CPURelease();
    void CPUDone();

    void SysLog();

    static const std::unordered_map<Event, void (EventsControl::*)()> actions;
};

inline const std::unordered_map<Event, void (EventsControl::*)()> EventsControl::actions = {
    { Event::MEM_ALLOC,         &EventsControl::memAlloc },
    { Event::MEM_FREE,          &EventsControl::memFree },

    { Event::IO_START_READ,     &EventsControl::IOStartRead },
    { Event::IO_START_WRITE,    &EventsControl::IOStartWrite },
    { Event::IO_COMPLETE,       &EventsControl::IOComplete },

    { Event::CPU_RUN,           &EventsControl::CPURun },
    { Event::CPU_RELEASE,       &EventsControl::CPURelease },
    { Event::CPU_DONE,          &EventsControl::CPUDone },

    { Event::SYS_LOG,           &EventsControl::SysLog },
};
