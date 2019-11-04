/**
 * job.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <tuple>

class Job {
public:
	Job() : id(5) {};
	~Job() {};

	void process(double duration) {};
	void complete() {};

	const int id;

	enum class Priority;
	enum class State;
	enum class Operation;

	std::tuple<Job::Operation, double> getNextOperation();

private:
	int currentCycle;

	int totalCycles;
	float memoryUsed;
	Job::Priority priority;
	int totalIO;

	int arriveTime;
	int startTime;

	Job::State state;

	static int lastId;
};

inline int Job::lastId = 0;

enum class Job::Priority {
	LOW,
	NORMAL,
	HIGH,
	CRITICAL,
};

enum class Job::State {
	SUBMIT,
	WAITING_RESOURCES,
	READY,
	RUNNING,
	WAITING_IO,
	DONE,
};

enum class Job::Operation {
	IO_READ,
	IO_WRITE,
	FINISH,
};
