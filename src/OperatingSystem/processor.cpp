/**
 * processor.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "processor.hpp"

#include <iostream>


/**
 * Inicia a execução de um 'job' e informa a próxima operação.
 * Retorna uma tupla referente ao próximo evento.
 */
PredictedEvent Processor::run(Job *job, int time) {
    if (this->isRunning)
        throw Error::CPU_UNAVAILABLE;
    
    this->time = time;
    this->job = job;
    this->isRunning = true;

    PredictedEvent nextEvent;

    switch (auto [timeUntil, operation, value] = this->job->getNextOperation(); operation) {
    case Job::Operation::IO_READ:
    case Job::Operation::IO_WRITE:
        nextEvent = { this->job->id, timeUntil, Event::CPU_RELEASE };
        break;

    case Job::Operation::FINISH:
        nextEvent = { this->job->id, timeUntil, Event::CPU_DONE };
        break;

    default:
        throw "Operação não reconhecida na CPU.";
    }

    return nextEvent;
}


/**
 * Libera o uso da CPU e atualiza o 'job' para o ponto onde a CPU
 * foi liberada. Este ponto deve ser referente ao ponto da próxima
 * operação onde é previsto que o 'job' seja interrompido.
 * Outros tipos de paradas devem ser tratadas como interrupções.
 */
PredictedEvent Processor::release(int time) {
    if (!isRunning)
        throw "Tentativa de parar a CPU quando ela já estava parada.";

    PredictedEvent nextEvent = { this->job->id, 0, Event::CPU_RUN };

    if (auto [timeUntil, operation, value] = this->job->getNextOperation(); timeUntil == time - this->time) {
        switch (operation) {
        case Job::Operation::IO_READ:
            nextEvent = { this->job->id, 0, Event::IO_START_READ };
            break;

        case Job::Operation::IO_WRITE:
            nextEvent = { this->job->id, 0, Event::IO_START_WRITE };
            break;

        case Job::Operation::FINISH:
            nextEvent = { this->job->id, 0, Event::MEM_FREE };
            break;

        default:
            throw "Operação de parada de processo não reconhecida na CPU.";
        }
    }

    this->job->process(time - this->time);

    this->job = nullptr;
    this->time = time;
    this->isRunning = false;

    return nextEvent;
}

/**
 * Exibe informações referentes ao processador.
 */
void Processor::info() {
    std::cout << "=== Processador ===" << std::endl;
    if (this->isRunning)
        std::cout << "Job atual: " << this->job->id << "." << std::endl;
    else
        std::cout << "Sem execucao no momento." << std::endl;

    std::cout << std::endl;
}
