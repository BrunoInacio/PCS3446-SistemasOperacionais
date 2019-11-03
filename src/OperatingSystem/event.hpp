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
	MEMORY_FULL,

	// Disco
	DISK_UNAVAILABLE,
	IO_COMPLETE
};


struct predictEvent {
	int id;
	double duration;
	Event event;
};