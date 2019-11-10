/**
 * event.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

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
    SYS_PAUSE,
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
