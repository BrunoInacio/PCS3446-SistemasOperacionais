/**
 * event.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "event.hpp"


void EventControl::addJobs(int num) {

}


void EventControl::run(int time) {

}


void EventControl::memAlloc() {

}


void EventControl::memFree() {

}


void EventControl::IOStartRead() {

}


void EventControl::IOStartWrite() {

}


void EventControl::IOComplete() {

}


void EventControl::CPURun() {

}


void EventControl::CPURelease() {

}


void EventControl::CPUDone() {

}


void EventControl::SysLog() {

}


bool predictedEvent::operator<(const predictedEvent e) {
    return this->time < e.time;
}
