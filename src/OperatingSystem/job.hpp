/**
 * job.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once


class Job {
public:
	Job();
	~Job() {};

	enum class Priority;
	enum class State;

private:
	const int id;
	int currentCycle;

	int totalCycles;
	float memoryUsed;
	Priority priority;
	int totalIO;

	int arriveTime;
	int startTime;

	State state;

	static int lastId;
};

inline int Job::lastId = 0;

enum class Job::Priority {
	Low,
	Normal,
	High,
	Critical
};

enum class Job::State {
	Submit,
	WaitingResources,
	Ready,
	Running,
	WaitingIO,
	Done
};
