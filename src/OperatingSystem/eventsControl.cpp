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
    this->addEvent({ 0, this->time + duration, Event::SYS_PAUSE });

    try {
        while (!this->events.empty()) {
            auto e = this->events.front();
            this->events.pop_front();
            this->time = e.time;

            (this->*EventsControl::actions.at(e.event))();
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
    auto position = std::lower_bound(this->events.begin(), this->events.end(), event);
    this->events.insert(position, event);
}


void EventsControl::memAlloc() {
    std::cout << "memAlloc" << std::endl;
}


void EventsControl::memFree() {
    std::cout << "memFree" << std::endl;
}


void EventsControl::IOStartRead() {
    std::cout << "IOStartRead" << std::endl;
}


void EventsControl::IOStartWrite() {
    std::cout << "IOStartWrite" << std::endl;
}


void EventsControl::IOComplete() {
    std::cout << "IOComplete" << std::endl;
}


void EventsControl::CPURun() {
    std::cout << "CPURun" << std::endl;
}


void EventsControl::CPURelease() {
    std::cout << "CPURelease" << std::endl;
}


void EventsControl::CPUDone() {
    std::cout << "CPUDone" << std::endl;
}


/**
 * Pausa a máquina de estados e retorna o controle para o usuário.
 */
void EventsControl::sysPause() {
    throw "Sistema pausado no instante " + std::to_string(this->time) + "ms.\n";
}


/**
 * Exibe informações sobre os futuros eventos.
 */
void EventsControl::info() {
    std::cout << "=== FUTUROS EVENTOS ===" << std::endl;
    std::cout << " JOB ID |          EVENT |    TIME" << std::endl;

    for (const auto& event : this->events)
        std::cout << std::setw(7) << event.jobID
        << std::setw(17) << Translate::event.at(event.event)
        << std::setw(10) << event.time
        << std::endl;
}
