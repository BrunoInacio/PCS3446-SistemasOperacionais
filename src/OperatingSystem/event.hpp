/**
 * event.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

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

    // Job
    JOB_ARRIVE,
    JOB_DONE,

    // System
    SYS_PAUSE,
};


struct PredictedEvent {
    int jobID;
    int time;
    Event event;

    double size;

    bool operator <(const PredictedEvent e) {
        return this->time < e.time;
    }
};


enum class Error {
    // Memória
    MEMORY_FULL,

    // Disco
    DISK_UNAVAILABLE,

    // Processador
    CPU_UNAVAILABLE,
};


enum class State {
    SUBMIT,
    WAITING_RESOURCES,
    READY,
    RUNNING,
    WAITING_IO,
    DONE,
};


enum class Priority {
    LOW,
    NORMAL,
    HIGH,
    CRITICAL,
};


class Translate {
public:
    static const std::unordered_map<Event, std::string> event;
    static const std::unordered_map<State, std::string> state;
    static const std::unordered_map<Priority, std::string> priority;
};

inline const std::unordered_map<Event, std::string> Translate::event = {
    { Event::MEM_ALLOC,         "MEM_ALLOC"         },
    { Event::MEM_FREE,          "MEM_FREE"          },

    { Event::IO_START_READ,     "IO_START_READ"     },
    { Event::IO_START_WRITE,    "IO_START_WRITE"    },
    { Event::IO_COMPLETE,       "IO_COMPLETE"       },

    { Event::CPU_RUN,           "CPU_RUN"           },
    { Event::CPU_RELEASE,       "CPU_RELEASE"       },
    { Event::CPU_DONE,          "CPU_DONE"          },

    { Event::JOB_ARRIVE,        "JOB_ARRIVE"        },
    { Event::JOB_DONE,          "JOB_DONE"          },

    { Event::SYS_PAUSE,         "SYS_PAUSE"         },
};

inline const std::unordered_map<State, std::string> Translate::state = {
    { State::SUBMIT,            "SUBMIT"            },
    { State::WAITING_RESOURCES, "WAITING_RESOURCES" },
    { State::READY,             "READY"             },
    { State::RUNNING,           "RUNNING"           },
    { State::WAITING_IO,        "WAITING_IO"        },
    { State::DONE,              "DONE"              },
};

inline const std::unordered_map<Priority, std::string> Translate::priority = {
    { Priority::LOW,            "LOW"       },
    { Priority::NORMAL,         "NORMAL"    },
    { Priority::HIGH,           "HIGH"      },
    { Priority::CRITICAL,       "CRITICAL"  },
};
