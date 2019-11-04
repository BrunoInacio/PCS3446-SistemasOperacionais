/**
 * event.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

class EventList {
public:

};


enum class Event {
	// Memória
	MEM_ALLOC,

	// Disco
	IO_START_READ,
	IO_START_WRITE,
	IO_COMPLETE,

	// Processor
	CPU_RUN,
	CPU_DONE,
	CPU_IO_RELEASE,

	CPU_SWITCH_JOB,
};

enum class Error {
	// Memória
	MEMORY_FULL,

	// Disco
	DISK_UNAVAILABLE,

	// Processador
	CPU_UNAVAILABLE,
};

struct predictEvent {
	int jobID;
	double duration;
	Event event;
};
