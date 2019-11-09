/**
 * operatingSystem.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "operatingSystem.hpp"

#include <iostream>


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


void OperatingSystem::info() {
    std::cout << "Informações do Sistema Operacional no atual estado." << std::endl;

    this->processor->info();
    this->memory->info();
    this->disk->info();
}
