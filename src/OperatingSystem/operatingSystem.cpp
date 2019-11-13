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
 * Adiciona job ao sistema operacional.
 */
PredictedEvent OperatingSystem::addJob(Job &&j) {
    this->jobs[j.id] = std::make_shared<Job>(j);
    return { j.id, 0, Event::MEM_ALLOC };
}


/**
 * Tenta iniciar o processamento de um job.
 */
PredictedEvent OperatingSystem::process(int jobID) {
    try {
        return this->processor->run(this->jobs.at(jobID), this->time);
    }
    catch (Error) {
        this->waitProcessor(jobID);
    }

    return { jobID, 0, Event::NONE };
}

/**
 * Tenta alocar um job para a memória principal do sistema.
 */
PredictedEvent OperatingSystem::memAlloc(int jobID) {
    try {
        this->memory->allocate(jobID, this->jobs.at(jobID)->memoryUsed);
        return { jobID, 0, Event::CPU_RUN };
    }
    catch (Error) {
        this->waitMemory(jobID);
    }

    return { 0, 0, Event::NONE };
}

/**
 * Tenta realizar uma operação de IO.
 */
PredictedEvent OperatingSystem::IO(int jobID, Disk::IO op, double size) {
    try {
        return this->disk->processIO(jobID, op, size);
    }
    catch (Error) {
        this->waitDisk(jobID, op, size);
    }

    return { 0, 0, Event::NONE };
}


/**
 * Executa o próximo job na fila do processador.
 */
PredictedEvent OperatingSystem::nextToProcessor() {
    if (this->jobToProcess.empty())
        return { 0, 0, Event::NONE };

    try {
        auto jobID = this->jobToProcess.front();
        PredictedEvent e = this->processor->run(this->jobs.at(jobID), this->time);
        this->jobToProcess.pop_front();
        return e;
    }
    catch (Error) {
        return { 0, 0, Event::NONE };
    }
}


/**
 * Aloca o próximo job na fila da memória.
 */
PredictedEvent OperatingSystem::nextToMemory() {
    if (this->jobToMemory.empty())
        return { 0, 0, Event::NONE };

    try {
        auto jobID = this->jobToMemory.front();
        this->memory->allocate(jobID, this->jobs.at(jobID)->memoryUsed);
        this->jobToMemory.pop_front();
        return { jobID, 0, Event::CPU_RUN };
    }
    catch (Error) {
        return { 0, 0, Event::NONE };
    }
}


/**
 * Aloca o próximo job na fila do disco.
 */
PredictedEvent OperatingSystem::nextToDisk() {
    if (this->jobToDisk.empty())
        return { 0, 0, Event::NONE };

    try {
        auto [jobID, op, size] = this->jobToDisk.front();
        auto e = this->disk->processIO(jobID, op, size);
        this->jobToDisk.pop_front();
        return e;
    }
    catch (Error) {
        return { 0, 0, Event::NONE };
    }
}


/**
 * Adiciona um job par a fila da memória.
 */
void OperatingSystem::waitMemory(int jobID) {
    this->jobToMemory.push_back(jobID);
}


/**
 * Adiciona um job par a fila do processador.
 */
void OperatingSystem::waitProcessor(int jobID) {
    this->jobToProcess.push_back(jobID);
}


/**
 * Adiciona um job par a fila do disco.
 */
void OperatingSystem::waitDisk(int jobID, Disk::IO op, double size) {
    this->jobToDisk.push_back(std::make_tuple(jobID, op, size));
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




/*
 * Define um job com valores estocásticos baseados em uma distribuição
 * estatística usual dos jobs.
 */
 Job OperatingSystem::stochasticJob() {
     std::random_device r;

     auto j = Job(10, 20, Priority::NORMAL);

     j.addOperation(std::make_tuple(5, Job::Operation::IO_READ, 35.0));
     j.addOperation(std::make_tuple(9, Job::Operation::IO_READ, 35.0));

     return j;
 }
