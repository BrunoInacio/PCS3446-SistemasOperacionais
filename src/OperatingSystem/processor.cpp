/**
 * processor.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "processor.hpp"


/**
 * Inicia a execução de um 'job' e informa a próxima operação.
 * Retorna uma tupla referente ao próximo evento.
 */
std::tuple<int, Event, double> Processor::runJob(Job *job) {
	if (this->isRunning)
		throw Error::CPU_UNAVAILABLE;

	std::tuple<int, Event, double> nextEvent;

	this->job = job;
	this->isRunning = true;

	switch (auto [operation, duration] = this->job->getNextOperation(); operation) {
	case Job::Operation::IO_READ:
	case Job::Operation::IO_WRITE:
		nextEvent = std::make_tuple(this->job->id, Event::CPU_IO_RELEASE, duration);
		break;

	case Job::Operation::FINISH:
		nextEvent = std::make_tuple(this->job->id, Event::CPU_DONE, duration);
		break;

	default:
		throw "Operação não reconhecida na CPU.";
	}

	return nextEvent;
}


std::tuple<int, Event, double> Processor::releaseJob() {
	auto jobID = this->job->id;
	std::tuple<int, Event, double> nextEvent;

	switch (auto [operation, duration] = this->job->getNextOperation(); operation) {
	case Job::Operation::IO_READ:
		this->job->process(duration);
		nextEvent =  std::make_tuple(jobID, Event::IO_START_READ, 0.0);
		break;

	case Job::Operation::IO_WRITE:
		this->job->process(duration);
		nextEvent = std::make_tuple(jobID, Event::IO_START_WRITE, 0.0);
		break;

	default:
		throw "Operação de parada de processo não reconhecida na CPU.";
	}

	this->job = nullptr;
	this->isRunning = false;

	return nextEvent;
}

int Processor::finishJob() {
	auto jobID = this->job->id;

	this->job->complete();

	this->job = nullptr;
	this->isRunning = false;

	return jobID;
}
