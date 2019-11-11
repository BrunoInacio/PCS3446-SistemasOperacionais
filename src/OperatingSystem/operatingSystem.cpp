/**
 * operatingSystem.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "operatingSystem.hpp"

#include <iostream>
#include <iomanip>


OperatingSystem::OperatingSystem()
    :processor(nullptr),
     memory(nullptr),
     disk(nullptr) {
}

void OperatingSystem::addProcessor(Processor &&p) {
    this->processor = std::make_unique<Processor>(p);
}


void OperatingSystem::addMemory(Memory &&m) {
    this->memory = std::make_unique<Memory>(m);
}


void OperatingSystem::addDisk(Disk &&d) {
    this->disk = std::make_unique<Disk>(d);
}


void OperatingSystem::addStochasticJobs(int num) {
    for (auto i = 0; i < num; i++) {
        Job job = Job(10, 20, Priority::NORMAL);
        int startTime = num;

        this->jobs.insert({ job.id, job });
        //this->addEvent({ job.id, startTime, Event::MEM_ALLOC });
    }
}


/**
 * Exibe informação sobre todos os jobs no sistema.
 */
void OperatingSystem::infoJobs() {
    std::cout << "=== JOBS ===" << std::endl;
    std::cout << " ID | PRIORITY |            STATUS | TIME NEEDED | MEMORY NEEDED" << std::endl;

    for (const auto& [jobID, job] : this->jobs)
        std::cout << std::setw(3) << job.id
        << std::setw(11) << Translate::priority.at(job.priority)
        << std::setw(20) << Translate::state.at(job.state)
        << std::setw(14) << job.totalTime
        << std::setw(16) << job.memoryUsed
        << std::endl;
}


void OperatingSystem::info() {
    std::cout << "Informações do Sistema Operacional no atual estado." << std::endl;

    this->processor->info();
    this->memory->info();
    this->disk->info();
}
