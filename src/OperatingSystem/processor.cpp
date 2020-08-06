/**
 * processor.cpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "processor.hpp"

#include <iostream>


/**
 * Inicia a execução de um 'job'.
 */
Processor::Result Processor::run(std::shared_ptr<Job> job) {
    if (this->isRunning)
        return Processor::Result::ERROR_CPU_UNAVAILABLE;
  
    this->job = job;
    this->isRunning = true;

    return Processor::Result::SUCCESS;
}

/**
 * Informa a próxima operação de parada a ser realizada.
 */
PredictedEvent Processor::getNextRelease() {
    switch (const auto& op = this->job->getNextOperation(); op.operation) {
    case Job::OperationType::IO_READ:
    case Job::OperationType::IO_WRITE:
        return { this->job->id, op.instant, Event::CPU_RELEASE };

    case Job::OperationType::FINISH:
        return { this->job->id, op.instant, Event::CPU_DONE };

    default:
        throw "Operação não reconhecida na CPU.";
    }
}

/**
 * Libera o uso da CPU e atualiza o 'job' para o ponto onde a CPU
 * foi liberada. Este ponto deve ser referente ao ponto da próxima
 * operação onde é previsto que o 'job' seja interrompido.
 * Outros tipos de paradas devem ser tratadas como interrupções.
 */
PredictedEvent Processor::release(int time) {
    if (!isRunning)
        return { 0, 0, Event::NONE };

    PredictedEvent nextEvent = { this->job->id, 0, Event::CPU_RUN };

    if (const auto& op = this->job->getNextOperation(); op.instant == time) {
        switch (op.operation) {
        case Job::OperationType::IO_READ:
            nextEvent = { this->job->id, 0, Event::IO_START_READ };
            break;

        case Job::OperationType::IO_WRITE:
            nextEvent = { this->job->id, 0, Event::IO_START_WRITE };
            break;

        case Job::OperationType::FINISH:
            nextEvent = { this->job->id, 0, Event::MEM_FREE };
            break;

        default:
            throw "Operação de parada de processo não reconhecida na CPU.";
        }
    }

    this->job->process(time);

    this->job = nullptr;
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
