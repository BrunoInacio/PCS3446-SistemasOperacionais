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
	static int lastId;
	const int id;

	Priority priority;
	State state;
};

int Job::lastId = 0;

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
