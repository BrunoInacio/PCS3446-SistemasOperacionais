/**
 * interface.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"
#include "eventsControl.hpp"

struct Interface {
    Interface() {};

    void start();
    void addMachine();
    void menu();

    EventsControl events;
};
