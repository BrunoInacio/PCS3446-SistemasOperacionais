/**
 * eventsControl.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "operatingSystem.hpp"

#include <deque>
#include <unordered_map>


class EventsControl {
public:
    EventsControl() : time(0) {}

    void run(int time);
    void info();

    void addEvent(PredictedEvent event);

private:
    int time;

    std::deque<PredictedEvent> events;

    void memAlloc();
    void memFree();

    void IOStartRead();
    void IOStartWrite();
    void IOComplete();

    void CPURun();
    void CPURelease();
    void CPUDone();

    void sysPause();

    static const std::unordered_map<Event, void (EventsControl::*)()> actions;
};

inline const std::unordered_map<Event, void (EventsControl::*)()> EventsControl::actions = {
    { Event::MEM_ALLOC,         &EventsControl::memAlloc        },
    { Event::MEM_FREE,          &EventsControl::memFree         },

    { Event::IO_START_READ,     &EventsControl::IOStartRead     },
    { Event::IO_START_WRITE,    &EventsControl::IOStartWrite    },
    { Event::IO_COMPLETE,       &EventsControl::IOComplete      },

    { Event::CPU_RUN,           &EventsControl::CPURun          },
    { Event::CPU_RELEASE,       &EventsControl::CPURelease      },
    { Event::CPU_DONE,          &EventsControl::CPUDone         },

    { Event::SYS_PAUSE,         &EventsControl::sysPause        },
};
