/**
 * eventsControl.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "eventsControl.hpp"

#include <algorithm>

#include <iostream>
#include <iomanip>
#include <string>


/**
 * Roda a máquina por um determinado intervalo de tempo 'time'.
 */
void EventsControl::run(int duration) {
    this->addEvent({ 0, duration, Event::SYS_PAUSE });

    try {
        while (!this->events.empty()) {
            auto e = this->events.front();
            this->events.pop_front();
            this->time = e.time;
            this->OS->time = this->time;

            auto newEvent = (this->*EventsControl::actions.at(e.event))(e);
            this->addEvent(newEvent);
        }
    }
    catch (std::string err) {
        std::cout << err << std::endl;
    }
}


/**
 * Adiciona 'event' à máquina.
 */
void EventsControl::addEvent(PredictedEvent event) {
    if (event.event == Event::NONE)
        return;

    event.time += this->time;

    auto position = std::lower_bound(this->events.begin(), this->events.end(), event);
    this->events.insert(position, event);
}


/**
 * Adiciona um Sistema operacional à máquina.
 */
void EventsControl::addOS(OperatingSystem&& OS) {
    this->OS = std::make_unique<OperatingSystem>(OS);
}


/**
 * Adiciona um job ao SO.
 */
PredictedEvent EventsControl::jobArrive(PredictedEvent e) {
    auto nextEvent = this->OS->addJob(this->OS->stochasticJob());

    std::cout << "[" << Translate::event.at(e.event) << "] " << this->time
        << ": O job " << nextEvent.jobID << " foi adicionado ao sistema."
        << std::endl;

    return nextEvent;
}


/**
 * Envia pedido para o SO para alocação de um job na memória.
 */
PredictedEvent EventsControl::memAlloc(PredictedEvent e) {
    this->OS->jobs.at(e.jobID)->state = State::WAITING_RESOURCES;
    return this->OS->memAlloc(e.jobID);
}


/**
 * Libera a memória usada pelo job e envia pedido para o SO
 * rodar a lista de espera pela memória.
 */
PredictedEvent EventsControl::memFree(PredictedEvent e) {
    this->OS->memory->free(e.jobID);

    auto chainEvent = this->OS->nextToMemory();

    if (chainEvent.event != Event::NONE)
        this->OS->jobs.at(chainEvent.jobID)->state = State::READY;

    return chainEvent;
}


/**
 * Solicita o início de uma operação de Entrada.
 */
PredictedEvent EventsControl::IOStartRead(PredictedEvent e) {
    std::cout << "[" << Translate::event.at(e.event) << "] " << this->time
        << ": O job " << e.jobID << " requisitou acesso de leitura do disco."
        << std::endl;

    this->OS->jobs.at(e.jobID)->state = State::WAITING_IO;
    return this->OS->IO(e.jobID, Disk::IO::READ, e.size);
}


/**
 * Solicita o início de uma operação de Saída.
 */
PredictedEvent EventsControl::IOStartWrite(PredictedEvent e) {
    std::cout << "[" << Translate::event.at(e.event) << "] " << this->time
        << ": O job " << e.jobID << " requisitou acesso de escrita no disco."
        << std::endl;

    this->OS->jobs.at(e.jobID)->state = State::WAITING_IO;
    return this->OS->IO(e.jobID, Disk::IO::WRITE, e.size);
}


/**
 * Libera o disco para ser usado e envia comando para o SO rodar
 * a lista de espera pelo disco.
 */
PredictedEvent EventsControl::IOComplete(PredictedEvent e) {
    std::cout << "[" << Translate::event.at(e.event) << "] " << this->time
        << ": O job " << e.jobID << " finalizou acesso ao disco."
        << std::endl;

    this->OS->jobs.at(e.jobID)->state = State::READY;

    auto newEvent = this->OS->disk->completeIO();

    if (auto chainEvent = this->OS->nextToDisk(); chainEvent.event != Event::NONE) {
        this->OS->jobs.at(chainEvent.jobID)->state = State::WAITING_IO;
        this->addEvent(chainEvent);
    }

    return newEvent;
}


/**
 * Envia pedido para o SO para executar um job no processador.
 */
PredictedEvent EventsControl::CPURun(PredictedEvent e) {
    this->OS->jobs.at(e.jobID)->state = State::READY;

    auto newEvent = this->OS->process(e.jobID);

    if (newEvent.event != Event::NONE)
        this->OS->jobs.at(newEvent.jobID)->state = State::RUNNING;

    return newEvent;
}


/**
 * Interrompe o uso da CPU e envia um novo processo para ela.
 */
PredictedEvent EventsControl::CPURelease(PredictedEvent e) {
    this->OS->jobs.at(e.jobID)->state = State::READY;

    auto newEvent = this->OS->processor->release(this->time);

    if (auto chainEvent = this->OS->nextToProcessor(); chainEvent.event != Event::NONE) {
        this->OS->jobs.at(chainEvent.jobID)->state = State::RUNNING;
        this->addEvent(chainEvent);
    }

    return newEvent;
}


/**
 * Finaliza o uso da CPU e envia um novo processo para ela.
 */
PredictedEvent EventsControl::CPUDone(PredictedEvent e) {
    std::cout << "[" << Translate::event.at(e.event) << "] " << this->time
        << ": O job " << e.jobID << " foi finalizado."
        << std::endl;

    this->OS->jobs.at(e.jobID)->state = State::DONE;

    auto newEvent = this->OS->processor->release(this->time);

    if (auto chainEvent = this->OS->nextToProcessor(); chainEvent.event != Event::NONE) {
        this->OS->jobs.at(chainEvent.jobID)->state = State::RUNNING;
        this->addEvent(chainEvent);
    }

    return newEvent;
}


/**
 * Pausa a máquina de estados e retorna o controle para o usuário.
 */
PredictedEvent EventsControl::sysPause(PredictedEvent e) {
    throw "[" + Translate::event.at(e.event) +"] Sistema pausado no instante " +
          std::to_string(e.time) + "ms.\n";
}


/**
 * Exibe informações sobre os futuros eventos.
 */
void EventsControl::info() {
    std::cout << "=== FUTUROS EVENTOS ===" << std::endl;
    std::cout << " JOB ID |          EVENT |    TIME" << std::endl;

    for (const auto& e : this->events)
        std::cout << std::setw(7) << e.jobID
        << std::setw(17) << Translate::event.at(e.event)
        << std::setw(10) << e.time
        << std::endl;
}
