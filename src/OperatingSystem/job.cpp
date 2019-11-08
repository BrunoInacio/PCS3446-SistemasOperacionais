/**
 * job.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "job.hpp"

#include <algorithm>


/**
 * Construtor que recebe 'totalTime', 'memoryUsed', 'totalIO' e 'priority'.
 */
Job::Job(int totalTime, double memoryUsed, Job::Priority priority)
    : totalTime(totalTime),
      memoryUsed(memoryUsed),
      priority(priority),
      id(++lastId),
      processedTime(0),
      state(Job::State::SUBMIT) {
    this->operations.push_back(std::make_tuple(totalTime, Job::Operation::FINISH, 0.0));
}


/**
 * Adiciona uma operação à lista de operações que devem ser realizadas pelo job.
 */
void Job::addOperation(std::tuple<int, Job::Operation, double> operation) {
    auto position = std::lower_bound(this->operations.begin(), this->operations.end(), operation);
    this->operations.insert(position, operation);
}


/**
 * Realiza o processamento de 'duration' de tempo.
 */
void Job::process(int duration) {
    this->processedTime += duration;
}


/**
 * Obtém a próxima operação que deve ser realizada pelo 'job'.
 * Por exemplo, operações de IO ou finalização do processamento.
 */
std::tuple<Job::Operation, int> Job::getNextOperation() {
    for (const auto [time, operation, value]: this->operations)
        if (this->processedTime < time)
            return std::make_tuple(operation, time - this->processedTime);

    return std::make_tuple(Job::Operation::FINISH, 0);
}
