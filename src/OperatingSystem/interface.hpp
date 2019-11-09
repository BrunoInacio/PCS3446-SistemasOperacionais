/**
 * interface.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "operatingSystem.hpp"
#include "event.hpp"
#include "eventsControl.hpp"

struct Interface {
    void start();
    void addHardware();
    void menu();

    OperatingSystem OS;
    EventsControl events;
};
