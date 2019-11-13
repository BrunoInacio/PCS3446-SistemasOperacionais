/**
 * operatingSystem.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "operatingSystem.hpp"

#include <algorithm>

#include <random>
#include <algorithm>

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
        auto [_, jobID] = this->jobToProcess.front();
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
        auto [_, jobID] = this->jobToMemory.front();
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
        auto [_, waitJob] = this->jobToDisk.front();
        auto [jobID, op, size] = waitJob;
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
    auto waitJob = std::make_pair(static_cast<int>(this->jobs.at(jobID)->priority), jobID);

    auto position = std::lower_bound(this->jobToMemory.begin(), this->jobToMemory.end(), waitJob);
    this->jobToMemory.insert(position, waitJob);
}


/**
 * Adiciona um job par a fila do processador.
 */
void OperatingSystem::waitProcessor(int jobID) {
    auto waitJob = std::make_pair(static_cast<int>(this->jobs.at(jobID)->priority), jobID);

    auto position = std::lower_bound(this->jobToProcess.begin(), this->jobToProcess.end(), waitJob);
    this->jobToProcess.insert(position, waitJob);
}


/**
 * Adiciona um job par a fila do disco.
 */
void OperatingSystem::waitDisk(int jobID, Disk::IO op, double size) {
    auto waitJob = std::make_pair(static_cast<int>(this->jobs.at(jobID)->priority), std::make_tuple(jobID, op, size));

    auto position = std::lower_bound(this->jobToDisk.begin(), this->jobToDisk.end(), waitJob);
    this->jobToDisk.insert(position, waitJob);
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
     int memSizeTable[] = { 15, 75, 200, 400, 500 };
     int totalTimeTable[] = { 15, 50, 100, 250, 1000 };
     int fileSizeTable[] = { 1, 5, 20, 200, 1000 };

     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<> dis(0.0, 1.0);

     auto memPos = dis(gen);
     int memSize = memSizeTable[(memPos > .9) + (memPos > .7) + (memPos > .3) + (memPos > .1)];

     auto timePos = dis(gen);
     int totalTime = totalTimeTable[(timePos > .9) + (timePos > .7) + (timePos > .3) + (timePos > .1)];

     auto priorityPos = dis(gen);
     Priority priority = static_cast<Priority>((timePos > .9) + (timePos > .7) + (timePos > .3));

     auto j = Job(totalTime, memSize, priority);

     auto disIO = dis(gen);
     auto numIO = (disIO > .9) + (disIO > .7) + 2*(disIO > .3) + 2*(disIO > .1);

     for (auto i = 1; i <= numIO; i++) {
         Job::Operation op = dis(gen) > .66 ? Job::Operation::IO_WRITE : Job::Operation::IO_READ;

         auto filePos = dis(gen);
         int fileSize = fileSizeTable[(timePos > .9) + (timePos > .7) + (timePos > .3) + (timePos > .1)];

         j.addOperation(std::make_tuple(i * (totalTime - 1) / numIO, op, fileSize));
     }

     return j;
 }
