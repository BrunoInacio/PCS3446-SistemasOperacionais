/**
 * eventsControl.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "operatingSystem.hpp"

#include <memory>
#include <deque>
#include <unordered_map>


class EventsControl {
public:
    EventsControl() : time(0), OS(nullptr) {};
    ~EventsControl() {};

    void run(int time);
    void addEvent(PredictedEvent event);

    void info();

    void addOS(OperatingSystem&& OS);
    std::unique_ptr<OperatingSystem> OS;

private:
    int time;

    std::deque<PredictedEvent> events;

    PredictedEvent memAlloc(PredictedEvent e);
    PredictedEvent memFree(PredictedEvent e);

    PredictedEvent IOStartRead(PredictedEvent e);
    PredictedEvent IOStartWrite(PredictedEvent e);
    PredictedEvent IOComplete(PredictedEvent e);

    PredictedEvent CPURun(PredictedEvent e);
    PredictedEvent CPURelease(PredictedEvent e);
    PredictedEvent CPUDone(PredictedEvent e);

    PredictedEvent jobArrive(PredictedEvent e);
    PredictedEvent jobDone(PredictedEvent e);

    PredictedEvent sysPause(PredictedEvent e);

    static const std::unordered_map<Event, PredictedEvent(EventsControl::*)(PredictedEvent)> actions;
};


inline const std::unordered_map<Event, PredictedEvent(EventsControl::*)(PredictedEvent)> EventsControl::actions = {
    { Event::MEM_ALLOC,         &EventsControl::memAlloc        },
    { Event::MEM_FREE,          &EventsControl::memFree         },

    { Event::IO_START_READ,     &EventsControl::IOStartRead     },
    { Event::IO_START_WRITE,    &EventsControl::IOStartWrite    },
    { Event::IO_COMPLETE,       &EventsControl::IOComplete      },

    { Event::CPU_RUN,           &EventsControl::CPURun          },
    { Event::CPU_RELEASE,       &EventsControl::CPURelease      },
    { Event::CPU_DONE,          &EventsControl::CPUDone         },

    { Event::JOB_ARRIVE,        &EventsControl::jobArrive       },
    { Event::JOB_DONE,          &EventsControl::jobDone         },

    { Event::SYS_PAUSE,         &EventsControl::sysPause        },
};
