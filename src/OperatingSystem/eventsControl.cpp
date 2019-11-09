/**
 * eventsControl.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "eventsControl.hpp"

#include <iostream>

void EventsControl::run(int time) {

}


void EventsControl::addStochasticJobs(int num) {
    for (auto i = 0; i < num; i++) {
        Job job = Job(10, 20, Job::Priority::NORMAL);
        this->jobs.insert({ job.id, job });
    }
}

void EventsControl::memAlloc() {

}


void EventsControl::memFree() {

}


void EventsControl::IOStartRead() {

}


void EventsControl::IOStartWrite() {

}


void EventsControl::IOComplete() {

}


void EventsControl::CPURun() {

}


void EventsControl::CPURelease() {

}


void EventsControl::CPUDone() {

}


void EventsControl::SysLog() {

}


bool EventsControl::PredictedEvent::operator<(const PredictedEvent e) {
    return this->time < e.time;
}


void EventsControl::infoJobs() {
    std::cout << "=== JOBS ===" << std::endl;
    for (const auto& [jobID, job] : this->jobs)
        std::cout << job.id << std::endl;
}
