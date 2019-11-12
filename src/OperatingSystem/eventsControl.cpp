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


void EventsControl::addOS(OperatingSystem &&OS) {
    this->OS = std::make_unique<OperatingSystem>(OS);
}

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

            (this->*EventsControl::actions.at(e.event))(e);
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


void EventsControl::memAlloc(PredictedEvent e) {
    std::cout << "memAlloc" << std::endl;
}


void EventsControl::memFree(PredictedEvent e) {
    std::cout << "memFree" << std::endl;
}


void EventsControl::IOStartRead(PredictedEvent e) {
    std::cout << "IOStartRead" << std::endl;
}


void EventsControl::IOStartWrite(PredictedEvent e) {
    std::cout << "IOStartWrite" << std::endl;
}


void EventsControl::IOComplete(PredictedEvent e) {
    std::cout << "IOComplete" << std::endl;
}


void EventsControl::CPURun(PredictedEvent e) {
    std::cout << "CPURun" << std::endl;
}


void EventsControl::CPURelease(PredictedEvent e) {
    std::cout << "CPURelease" << std::endl;
}


void EventsControl::CPUDone(PredictedEvent e) {
    std::cout << "CPUDone" << std::endl;
}


/**
 * Pausa a máquina de estados e retorna o controle para o usuário.
 */
void EventsControl::sysPause(PredictedEvent e) {
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
