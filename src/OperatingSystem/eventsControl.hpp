/**
 * eventsControl.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "operatingSystem.hpp"
#include "job.hpp"

#include <deque>
#include <unordered_map>


class EventsControl {
public:
    EventsControl() : time(0) {}

    void addStochasticJobs(int num);
    void run(int time);
    void infoJobs();
    void info();

private:
    int time;
    std::unordered_map<int, Job> jobs;

    struct PredictedEvent {
        int jobID;
        int time;
        Event event;

        bool operator <(const PredictedEvent e);
    };

    void addEvent(PredictedEvent event);
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

    static const std::unordered_map<Event, std::string> translateEvent;
    static const std::unordered_map<State, std::string> translateState;
    static const std::unordered_map<Priority, std::string> translatePriority;
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

inline const std::unordered_map<Event, std::string> EventsControl::translateEvent = {
    { Event::MEM_ALLOC,         "MEM_ALLOC"         },
    { Event::MEM_FREE,          "MEM_FREE"          },

    { Event::IO_START_READ,     "IO_START_READ"     },
    { Event::IO_START_WRITE,    "IO_START_WRITE"    },
    { Event::IO_COMPLETE,       "IO_COMPLETE"       },

    { Event::CPU_RUN,           "CPU_RUN"           },
    { Event::CPU_RELEASE,       "CPU_RELEASE"       },
    { Event::CPU_DONE,          "CPU_DONE"          },

    { Event::SYS_PAUSE,         "SYS_PAUSE"         },
};

inline const std::unordered_map<State, std::string> EventsControl::translateState = {
    { State::SUBMIT,            "SUBMIT"            },
    { State::WAITING_RESOURCES, "WAITING_RESOURCES" },
    { State::READY,             "READY"             },
    { State::RUNNING,           "RUNNING"           },
    { State::WAITING_IO,        "WAITING_IO"        },
    { State::DONE,              "DONE"              },
};

inline const std::unordered_map<Priority, std::string> EventsControl::translatePriority = {
    { Priority::LOW,            "LOW"       },
    { Priority::NORMAL,         "NORMAL"    },
    { Priority::HIGH,           "HIGH"      },
    { Priority::CRITICAL,       "CRITICAL"  },
};
