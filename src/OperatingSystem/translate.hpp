#pragma once

#include "event.hpp"
#include "job.hpp"

#include <unordered_map>

namespace Translate {
    inline const std::unordered_map<Event, std::string> event = {
        { Event::MEM_ALLOC,         "MEM_ALLOC"         },
        { Event::MEM_FREE,          "MEM_FREE"          },
        { Event::IO_START_READ,     "IO_START_READ"     },
        { Event::IO_START_WRITE,    "IO_START_WRITE"    },
        { Event::IO_COMPLETE,       "IO_COMPLETE"       },
        { Event::CPU_RUN,           "CPU_RUN"           },
        { Event::CPU_RELEASE,       "CPU_RELEASE"       },
        { Event::CPU_DONE,          "CPU_DONE"          },
        { Event::JOB_ARRIVE,        "JOB_ARRIVE"        },
        { Event::SYS_PAUSE,         "SYS_PAUSE"         },
    };

    inline const std::unordered_map<Job::State, std::string> state = {
        { Job::State::SUBMIT,            "SUBMIT"            },
        { Job::State::WAITING_RESOURCES, "WAITING_RESOURCES" },
        { Job::State::READY,             "READY"             },
        { Job::State::RUNNING,           "RUNNING"           },
        { Job::State::WAITING_IO,        "WAITING_IO"        },
        { Job::State::DONE,              "DONE"              },
    };

    inline const std::unordered_map<Job::Priority, std::string> priority = {
        { Job::Priority::LOW,            "LOW"               },
        { Job::Priority::NORMAL,         "NORMAL"            },
        { Job::Priority::HIGH,           "HIGH"              },
        { Job::Priority::CRITICAL,       "CRITICAL"          },
    };
}
