
/**
 * processor.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "job.hpp"

#include <tuple>

class Processor {
public:
	Processor() : job(nullptr), isRunning(0) {};
	~Processor() {};

	std::tuple<int, Event, double> runJob(Job *job);
	std::tuple<int, Event, double> releaseJob();
	int finishJob();

private:
	Job *job;
	bool isRunning;
};
