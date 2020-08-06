/**
 * interface.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brand�o In�cio
 */

#pragma once

#include "event.hpp"
#include "eventsControl.hpp"

struct Interface {
    Interface() {};

    void start();
    void createMachine();
    void menu();

    EventsControl events;
};
