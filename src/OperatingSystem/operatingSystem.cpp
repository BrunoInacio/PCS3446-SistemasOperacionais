/**
 * operatingSystem.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "operatingSystem.hpp"

#include <algorithm>

#include <random>
#include <iostream>
#include <iomanip>
#include <string>


OperatingSystem::OperatingSystem()
    : processor(nullptr),
      memory(nullptr),
      disk(nullptr) {
}


/**
 * Adiciona o processador que será utilizado pelo sistema.
 */
void OperatingSystem::addProcessor(Processor&& p) {
    this->processor = std::make_unique<Processor>(p);
}


/**
 * Adiciona a memória que será utilizada pelo sistema.
 */
void OperatingSystem::addMemory(Memory&& m) {
    this->memory = std::make_unique<Memory>(m);
}


/**
 * Adiciona o dsico que será utilizado pelo sistema.
 */
void OperatingSystem::addDisk(Disk&& d) {
    this->disk = std::make_unique<Disk>(d);
}


/**
 * Adiciona job ao sistema operacional.
 */
void OperatingSystem::addJob(Job &&j) {
    this->jobs[j.id] = std::make_unique<Job>(j);
}


/**
 * Exibe informação sobre todos os jobs no sistema.
 */
void OperatingSystem::info() {
    std::cout << "=== JOBS ===" << std::endl;
    std::cout << " ID | PRIORITY |            STATUS | TIME NEEDED | MEMORY NEEDED" << std::endl;

    for (const auto& [jobID, job] : this->jobs)
        std::cout << std::setw(3) << job->id
        << std::setw(11) << Translate::priority.at(job->priority)
        << std::setw(20) << Translate::state.at(job->state)
        << std::setw(14) << job->totalTime
        << std::setw(16) << job->memoryUsed
        << std::endl;
}


/**
 * Exibe informações sobre os dispostivos de hardware associados ao sistema.
 */
void OperatingSystem::infoHardware() {
    std::cout << "=== Dispositivos ===" << std::endl;

    this->processor->info();
    this->memory->info();
    this->disk->info();
}




/**
 * Define um job com valores estocásticos baseados em uma distribuição
 * estatística usual dos jobs.
 */
 /*std::tuple<int, Job> OperatingSystem::stochasticJob(int maxTime) {
     std::random_device r;

     int time = 0;

     return std::make_tuple(time, Job(10, 20, Priority::NORMAL));
 }*/